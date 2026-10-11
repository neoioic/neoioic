# OIOIC 核心代码审查报告

审查日期：2026-10-11。主要范围为 `include/o.h`、`include/oioic.h`、`src/o.c`、`src/oioic.c`；同时追踪了教学示例的构造代码和宿主创建/销毁路径，以核对运行时的实际使用方式。已阅读 AGENTS.md、README 及架构、构建、教程、代码风格文档。本报告不代表对 WGI 全部业务代码的完整审计。

项目以节点图表达 C 对象的继承与组合：AND 保存节点，AIB 决定直接基节点访问顺序，ABN 保存全部基节点，ACS 按调用者/委托者登记一次访问。构造函数负责内存布局，TOG 负责绑定接口，VO 包装负责登记和清理，继承宏负责分派。以下问题按这一责任划分审查，不把文档明确交给应用的线程同步列为缺陷。

所有修复代码均为建议，未应用到源码。省略号表示原代码节选；涉及布局或生命周期协议的修复明确标为设计示意，不能直接粘贴替换。

## 1. 队列以数组前一个地址表示空队列，且先生成越界指针再取模

### 1、代码位置

`src/o.c:166`、`src/o.c:217–218`、`src/o.c:234`；`src/oioic.c:100–103`、`src/oioic.c:166–167`、`src/oioic.c:181–182`；`include/o.h:408`、`include/o.h:452`。构造函数也使用相同哨兵，例如 `examples/single_inheritance/so/go/car/car.c:152–156`。

```c
new_rear = pq->data + (pq->rear + qty_enq - pq->data) % pq->capacity;
new_front = pq->data +
	    (pq->front + qty_deq - pq->data) % pq->capacity;
/* 队列清空后 */
pq->front = pq->rear = pq->data - 1;
/* CMD_RESET */
members->iq.front = members->iq.rear = members->iq.data - 1;
```

### 2、问题内容

C 只允许形成数组内部或尾后一位的指针，`data - 1` 本身已是未定义行为，不以是否解引用为条件。零容量对象的 `data` 为 NULL，正常发送 CMD_RESET 还会执行 NULL 指针减一。

环绕时的 `front + qty_deq`、`rear + qty_enq` 也可能超过尾后一位。例如容量为 8，front 位于索引 6，读取 4 字节时先形成索引 10 的指针；后续相减和取模不能消除已经发生的未定义行为。现有 x86_64 示例运行成功不能证明这些运算符合 C11。

### 3、修复方案

统一采用合法的环形表示：空队列由 quantity 判断；有存储时 front/rear 始终位于数组内，rear 表示下一次写入位置；无存储时两者为 NULL。先算整数偏移，再生成数组内指针，并同步修改三个单字节宏、重置、扩容和全部构造代码。

```c
/* 构造、清空、重置：capacity == 0 时 data == NULL。 */
q->front = q->rear = q->data;
q->quantity = q->lost = 0;

/* 入列核心示意：已确认 capacity > 0，qty_enq > 0。 */
size_t rear = (size_t)(q->rear - q->data);
size_t first = q->capacity - rear;
if (first > qty_enq)
	first = qty_enq;
memcpy(q->data + rear, input_data, first);
memcpy(q->data, input_data + first, qty_enq - first);
size_t tail = q->capacity - rear;
size_t next = qty_enq >= tail ? qty_enq - tail : rear + qty_enq;
q->rear = q->data + next;
q->quantity += qty_enq;
```

上述分段偏移利用 `qty_enq <= capacity` 的队列不变量，避免先做可能溢出的整数加法。出列同样按整数索引分段复制和移动 front。

复核：这是 C 指针运算规则问题，未声称已通过运行触发崩溃。

## 2. 调整队列容量先释放旧空间，分配失败后留下失效队列

### 1、代码位置

`src/oioic.c:159–188`，输入/输出队列两个分支相同。

```c
if (members->iq.data != NULL)
	free(members->iq.data);
members->iq.data = (unsigned char *)calloc(
	*((unsigned int *)input_stream), 1);
if (members->iq.data != NULL) {
	members->iq.front = members->iq.rear = members->iq.data - 1;
	members->iq.capacity = *((unsigned int *)input_stream);
	members->iq.quantity = members->iq.lost = 0;
	return R_P;
} else {
	return R_N;
}
```

### 2、问题内容

calloc 失败时 data 变为 NULL，但 capacity、quantity、front、rear 保留旧值，后两者指向已释放空间。调用者收到失败后继续使用原队列，enqueue/dequeue 会访问失效存储；即使调用者停止使用，查询旧容量仍得到误导性结果。

此外，input_stream 若来自旧队列的数据区，free 后读取新容量即发生释放后读取；分配成功后再次读取 input_stream 仍存在同一问题。

实际故障注入：原队列容量 8、数据量 2，新容量 16 的 calloc 被强制返回 NULL。结果为 `R_N=-1003`，但队列为 `data=NULL, capacity=8, quantity=2`，front 仍等于旧地址。未继续解引用悬空指针。

### 3、修复方案

先把参数复制到局部变量，再分配新空间；成功后才释放旧空间并整体提交状态。零容量应明确表示禁用队列，避免依赖 calloc(0, 1) 的实现差异。以下还采用第 1 项建议的合法空队列表示。

```c
unsigned int new_capacity;
unsigned char *new_data = NULL;

if (!input_stream || quantity != sizeof(new_capacity))
	return RN_INVALIDARG;
memcpy(&new_capacity, input_stream, sizeof(new_capacity));
if (new_capacity) {
	new_data = calloc(new_capacity, 1);
	if (!new_data)
		return R_N;
}
free(q->data);
*q = (struct queue) {
	.data = new_data,
	.capacity = new_capacity,
	.front = new_data,
	.rear = new_data,
};
return R_P;
```

复核：iq/oq 均存在；根本问题不是分配失败本身，而是失败后仍暴露不一致状态。

## 3. 核心容量命令只用 assert 校验流尺寸，Release 会越界读写

### 1、代码位置

`src/oioic.c:128–136`、`src/oioic.c:159–183`；VO 入口只校验非零容量/数量，例如 `src/o.c:541–545`、`src/o.c:581–584`。

```c
case GET_IQCTY:
	assert(capacity >= sizeof(unsigned int));
	*((unsigned int *)output_stream) = members->iq.capacity;
	*output_quantity = sizeof(unsigned int);
	return R_P;
case SET_IQCTY:
	assert(sizeof(unsigned int) == quantity);
	/* 随后将 input_stream 解引用为 unsigned int。 */
```

### 2、问题内容

NDEBUG 删除 assert 后，GET_IQCTY/GET_OQCTY 会向不足 sizeof(unsigned int) 的输出缓冲区写入完整整数；SET_IQCTY/SET_OQCTY 则从过短输入读取完整整数。VO 包装无法阻止长度为 1 的调用。输入尺寸失效还可能先释放旧队列，再读取越界参数。

实际验证：使用 8 字节保护数组，但给 GET_IQCTY 声明 capacity=1；初始保护字节为 CC。Release 返回 R_P、output_quantity=4，索引 1–3 均被改为 00。这验证的是超过声明容量的写入；没有故意使用真实 1 字节分配导致进程崩溃。

### 3、修复方案

在命令处理处分支做运行时尺寸检查，并在校验成功前不修改队列；失败返回 RN_INVALIDARG，输出数量为 0。iq/oq 两组命令均需修改。

```c
unsigned int value = members->iq.capacity;
if (!output_quantity)
	return RN_INVALIDARG;
*output_quantity = 0;
if (!output_stream || capacity < sizeof(value))
	return RN_INVALIDARG;
memcpy(output_stream, &value, sizeof(value));
*output_quantity = sizeof(value);
return R_P;

/* 设置命令：在 free/calloc 之前检查。 */
if (!input_stream || quantity != sizeof(unsigned int))
	return RN_INVALIDARG;
```

复核：报告限定在核心已有明确固定数据尺寸的命令；没有把所有 API 的调用前置条件一概判为错误。

## 4. 字节流强转整数指针，隐含未声明的对齐和有效类型要求

### 1、代码位置

`src/oioic.c:130`、`src/oioic.c:135`、`src/oioic.c:164`、`src/oioic.c:168`、`src/oioic.c:179`、`src/oioic.c:183`。

```c
*((unsigned int *)output_stream) = members->iq.capacity;
members->iq.data = (unsigned char *)calloc(
	*((unsigned int *)input_stream), 1);
```

### 2、问题内容

公共接口接收 unsigned char 字节流，没有声明缓冲区必须按 unsigned int 对齐。调用者提供足够长度的字节数组或数据包内部偏移时，该地址可能不满足整数对齐；解引用强转后的指针产生未定义行为，在严格对齐平台可能异常。即使对齐，若实际存储是声明为 unsigned char[] 的对象，用 unsigned int 左值读写也存在有效类型/别名规则问题。

这是与长度越界不同的问题：容量完全足够仍可触发。当前 x86_64 通常允许未对齐硬件访问，不能据此声称 C 层面正确。

### 3、修复方案

保留现有本机整数数据格式，使用 memcpy 在字节流和正确对齐的局部整数之间转换，并与第 3 项运行时尺寸检查配合。

```c
unsigned int value;
memcpy(&value, input_stream, sizeof(value));
/* 输出 */
value = members->iq.capacity;
memcpy(output_stream, &value, sizeof(value));
```

复核：未把此问题扩展为网络字节序缺陷；协议是否需要跨平台序列化属于另一项设计决策。此项仅做静态规则核对。

## 5. _SBO_OBJECT_INTERACT0 丢弃基节点返回值

### 1、代码位置

`include/o.h:1247–1262`；返回约定见同文件 `815–817`。

```c
int ir = RO__SBOOIX;
/* ... */
if (R_P == register_caller(*(self->direct_bases + i), caller_context))
	(*(self->direct_bases + i))->interact0(
		*(self->direct_bases + i), action, caller_context);
/* ... */
return ir;
```

### 2、问题内容

该宏是 SBO 接力访问。文档约定单继承返回最终基节点执行结果，但 interact0 的调用结果完全未赋给 ir，因此即使唯一基节点返回 R_P 或 R_N，也固定返回 RO__SBOOIX。其他 _SBO 宏至少保存了基节点结果，表明此处遗漏赋值。

实际验证：一个直接基节点返回 R_P=1004，VO 调用实际得到 3（RO__SBOOIX）。现有示例使用 SBO 非接力宏，所以普通示例运行未覆盖此缺陷。

### 3、修复方案

保存返回值，并同时采用第 6 项正确的多继承返回规则。

```c
if (R_P == register_caller(base, caller_context))
	ir = base->interact0(base, action, caller_context);
/* 单继承传递结果，多继承返回接力专用中性结果。 */
return self->direct_base_count > 1 ? RO__SBOOIX : ir;
```

复核：应修复 _SBO_OBJECT_INTERACT0，不能误改本来就忽略基节点结果的 OBS 接力宏。

## 6. 其余 _SBO 接力宏在多继承时返回最后一个分支结果

### 1、代码位置

`include/o.h:960–977`、`1055–1073`、`1154–1173`、`1344–1364`、`1443–1462`、`1547–1568`。以 interact2 为例：

```c
int ir = RO__SBOOIX;
for (i = 0; i < self->direct_base_count; i++) {
	/* 登记成功后 */
	ir = (*(self->direct_bases + i))->interact2(
		*(self->direct_bases + i), action, input_stream,
		quantity, caller_context);
}
return ir;
```

### 2、问题内容

头文件明确规定 SBO 接力多继承返回 RO__SBOOIX，实际宏却无条件返回最后一个被执行分支的结果。这样对外返回值依赖直接基节点排序，以及某分支是否因重复登记而跳过；最后一个分支成功会掩盖之前分支失败，且违反分派专用中性结果的约定。

实际验证：两个直接基节点均返回 R_P，_SBO_OBJECT_INTERACT2 返回 1004，而约定值为 3。

### 3、修复方案

保留逐分支接力执行，在多分支节点返回约定中性值。七类 _SBO 宏应一起核对，包括第 5 项 interact0。

```c
return self->direct_base_count > 1 ? RO__SBOOIX : ir;
```

单继承链中的基节点若自身具有多继承，它返回的 RO__SBOOIX 会继续向上传递。不要用 RN(ir) 提前终止接力遍历，否则改变接力语义。

复核：报告依据当前头文件的明确约定，不将多分支接力“意义不大”解释为可任意返回结果。

## 7. 关闭中途失败只恢复自身引用计数，已关闭基节点未恢复

### 1、代码位置

`include/o.h:1571–1603`，尤其 `1578`、`1583–1599`。

```c
self->ref_count--;
for (i = 0; i < self->direct_base_count; i++) {
	if ((*(self->direct_bases + i))->ref_count - 1 == self->ref_count) {
		/* 登记并关闭该基节点，失败时： */
		if (RN(ir)) {
			self->ref_count++;
			return ir;
		}
	}
}
```

### 2、问题内容

假设父节点及两个独立直接基节点引用计数均为 1。第一个基节点关闭成功，降为 0；第二个返回 R_N（也可能是 ACS 席位耗尽导致登记失败）。宏只把父节点恢复为 1，留下计数 1/0/1。父对象看起来仍打开，但部分基节点已关闭，可能已释放业务资源。

重试关闭时，计数判断会跳过已关闭的第一个基节点，因此“恢复父引用计数”并不能恢复原对象状态。实际验证得到 `R_N=-1003, counts=1,0,1`。

### 3、修复方案

关闭需要统一的失败协议。对于可失败的关闭，应先按去重后的对象图预检并保留访问席位，确认全部节点可关闭，再提交资源释放与引用计数变更；提交阶段应约定不会失败。不能只保存/恢复计数，因为 free、销毁窗口等外部副作用无法靠恢复数字逆转。

核心流程设计示意（需要实现预检/提交职责，非现有可直接调用的函数）：

```c
/* 准备阶段不释放业务资源、不修改引用计数。
 * 收集需要关闭的节点，按 ACS 规则去重并保留席位。
 */
int result = prepare_close_graph(self, caller_context, &plan);
if (RN(result)) {
	release_close_plan(&plan);
	return result;
}
/* 全部准备成功后提交，约定本阶段不再失败。 */
commit_close_graph(&plan);
release_close_plan(&plan);
return self->ref_count == 0 ? RP_RCZERO : R_P;
```

若采用另一种明确的“允许部分关闭”协议，则必须返回可恢复的状态并提供继续清理路径，删除当前伪回滚；不能继续让调用者把失败理解为对象仍完整打开。打开宏内的 vo_close 回滚也应同步遵守选定协议。

复核：仅报告允许返回负结果时的中途失败路径；没有声称现有控制台示例正常关闭失败。

## 8. 构造函数的访问席位计算存在整数溢出和窄化截断

### 1、代码位置

`examples/multiple_inheritance/so/go/amphicar/amphicar.c:34`、`122`、`143`、`167`、`179`、`254`；`examples/single_inheritance/so/go/car/car.c:30`、`100`、`124`、`136`。`include/o.h:280` 将 caller_count 声明为 unsigned short。宿主例如 `examples/multiple_inheritance/ho.c:77–80` 只检查 caller_capacity >= 1。

```c
size_t ux_cs = caller_capacity * 12;
/* ... */
node->caller_count = caller_capacity * 4;
p += sizeof(struct vr) * node->caller_count;
```

### 2、问题内容

caller_capacity 是 int，乘法先以 int 运算，再赋给 size_t；足够大的正数会发生有符号溢出。size_t 左值不会自动把右侧乘法变成 size_t。

此外各节点的席位数赋给 unsigned short 后截断，而总分配量使用未截断的席位计算，创建可以返回成功但节点没有承诺的登记能力。实际对 amphicar 传入 65536，创建返回 R_P，五个节点 caller_count 均为 0，随后 vo_open 返回 R_N。更小的参数也可能先使某个基节点席位数截断。

### 3、修复方案

在任何分配/布局计算之前检查实际字段可表示范围；若要支持更大容量，直接把字段及遍历索引统一改为 size_t，并同步全部构造代码，不保留截断实现。乘法和总量累加还须检查 SIZE_MAX。

保留当前字段宽度时的核心检查示意（max_factor 从该构造图的最大席位倍数得出）：

```c
if (caller_capacity < 1 ||
    (size_t)caller_capacity > USHRT_MAX / max_factor)
	return RN_INVALIDARG;
size_t count = (size_t)caller_capacity;
if (count > SIZE_MAX / total_factor)
	return RN_INVALIDARG;
size_t ux_cs = count * total_factor;
if (ux_cs > (SIZE_MAX - fixed_size) / sizeof(struct vr))
	return RN_INVALIDARG;
size_t sum = fixed_size + ux_cs * sizeof(struct vr);
```

复核：这是示例所实现的构造职责，核心库自身没有 CRT 实现；修复应落在实际构造代码/构造模板，而不是塞入根库的构建脚本。

## 9. 外部存储构造路径没有初始化对象图，依赖调用者预先清零

### 1、代码位置

`examples/single_inheritance/so/go/car/car.c:44–49`、`58–78`、`131–190`；`examples/multiple_inheritance/so/go/amphicar/amphicar.c:49–54`、`63–97`、`174–233`。

```c
if (NULL == exotic_memory) {
	*object_out = NULL;
	p_ic = (unsigned char *)calloc(sum, 1);
} else {
	p_ic = exotic_memory;
}
/* 后续只设置部分字段；ref_count、ACS 空席位等未显式初始化。 */
if (input_capacity > 0) {
	/* 才初始化 iq。 */
}
```

### 2、问题内容

宿主注释支持已分配的外部存储（包括局部对象），没有要求必须是全零内存。动态路径的 calloc 自动清零，外部路径却直接使用旧内容。未设置的 ref_count、ACS 记录、OIOIC 的 base_count/bases，以及零容量队列和模式状态均可能保留垃圾值。

访问登记可能无法找到空席位；VO 返回后的 unregister_caller 可能按垃圾 base_count 遍历垃圾 bases；宿主销毁还可能 free 零容量队列中的垃圾指针。

实际验证：用 malloc 的足够大、正确对齐内存填充 A5，再构造 amphicar，返回 R_P，但首节点 ref_count=2779096485、OIOIC base_count=42405、iq.capacity=2779096485。验证只检查状态，未执行会解引用垃圾指针的访问/销毁。

### 3、修复方案

外部路径也应在建立节点图之前初始化全部构造空间，并显式要求外部容量和对齐有效。建议让接口接收外部容量，避免无从验证空间是否足够；外部存储必须处于未构造状态，不能覆盖仍拥有资源的活动对象。

```c
if (exotic_memory) {
	/* proposed 参数 exotic_capacity：同步宿主和 CRT 调用点。 */
	if (exotic_capacity < sum ||
	    (uintptr_t)exotic_memory % _Alignof(struct object))
		return RN_INVALIDARG;
	p_ic = exotic_memory;
	memset(p_ic, 0, sum);
} else {
	p_ic = calloc(sum, 1);
	if (!p_ic)
		return R_N;
}
```

还需核对所有实际布局类型的对齐，而不只 object；第 1 项队列合法初始表示也应同步实现。

复核：动态 calloc 路径没有此问题；这是公开支持的外部存储分支缺少初始化，不是要求构造函数替调用者清理活动对象。

## 10. OIOIC 根节点直接通过 VO 打开/关闭时缺少计数边界保护

### 1、代码位置

`src/oioic.c:17–20`、`src/oioic.c:219–222`。对照派生节点宏 `include/o.h:844–846`、`1576–1577`。

```c
static int oioic_open(struct object *self, const struct vr *caller_context)
{
	self->ref_count++;
	return R_P;
}
static int oioic_close(struct object *self, const struct vr *caller_context)
{
	self->ref_count--;
	return R_P;
}
```

### 2、问题内容

派生宏检查打开计数溢出和“尚未打开”，根接口却无条件增减。通过 get_base_node 获取真实 OIOIC 节点后再用 vo_open/vo_close，VO 只做登记，没有同类保护：关闭计数 0 的根节点使其变为 UINT_MAX；打开计数 UINT_MAX 的根节点使其变为 0，二者仍返回成功。

实际在具有合法 ACS 和成员状态的根节点上通过 VO 验证：`close(0)` 返回 R_P、计数 4294967295；`open(UINT_MAX)` 返回 R_P、计数 0。

### 3、修复方案

在根接口自身保护边界，保持失败时计数不变。如果架构决定禁止外部访问根生命周期，则应在 VO 层明确拒绝并落实这个约束，而非只依赖调用习惯。

```c
/* oioic_open；需要 limits.h。 */
if (self->ref_count == UINT_MAX)
	return RN_FULL;
self->ref_count++;
return R_P;

/* oioic_close */
if (!self->ref_count)
	return RO_NOPEN;
self->ref_count--;
return R_P;
```

复核：正常经派生节点宏访问时已有部分保护；此项特指根节点作为合法节点直接经 VO 访问的边界路径。

## 11. 外部存储对象耗尽 OID 时，宿主清理路径解引用 NULL 输出参数

### 1、代码位置

`examples/single_inheritance/ho.c:69–72`、`102–117`；`examples/multiple_inheritance/ho.c:77–80`、`118–133`；`examples/wgi/ho.c:145–160`。

```c
/* 外部存储路径合法组合为 object_out == NULL，exotic_memory != NULL。 */
if (!RN(fr)) {
	/* ... */
	if ((MSKSO & gs_tad.oid) < (MSKSO & oidbak)) {
		gs_tad.oid = oidbak;
		members = (struct em_oioic *)get_base_members(
			*object_out, MSN_OIOIC);
		/* 释放队列之后才区分外部存储。 */
		if (NULL == exotic_memory) {
			free(*object_out);
			*object_out = NULL;
		}
		return RN_LACKOID;
	}
}
```

### 2、问题内容

新对象需要多个节点 OID。当序号增加跨过低 16 位上限，宿主执行耗尽清理。外部存储模式明确要求 object_out 为 NULL，此处仍执行 `*object_out`，所以本应返回 RN_LACKOID 的受控失败变成 NULL 解引用。动态路径有有效 object_out，不存在同一 NULL 解引用。

### 3、修复方案

创建成功后先统一取得实际对象地址，清理队列后仅释放宿主拥有的动态对象空间；外部对象失败后的队列状态也应置空。更稳妥的设计是按需要的节点数预先保留 OID，避免构造完成后才发现溢出。

```c
struct object *created = exotic_memory ?
	(struct object *)exotic_memory : *object_out;
struct em_oioic *members = get_base_members(created, MSN_OIOIC);
free(members->iq.data);
free(members->oq.data);
members->iq = (struct queue){0};
members->oq = (struct queue){0};
if (!exotic_memory) {
	free(created);
	*object_out = NULL;
}
return RN_LACKOID;
```

复核：静态核对了合法参数组合、OID 递增以及失败分支的执行顺序；未大量创建对象来动态耗尽 OID。

## 验证与报告回查

实际执行：

- 根库及四个独立示例各执行 `xmake -P .`，当前配置构建检查均成功。多数目标使用现有构建缓存，未声称完整重编译或本次覆盖 Debug/Release 两种配置。
- 三个控制台示例分别执行 `xmake run -P . <目标名>`，退出码均为 0，输出正常。WGI 只检查构建，未启动窗口或做交互回归。
- GCC 15.1 对两份核心源文件执行 C11 语法与警告检查，通过，存在未使用参数、类型转换等警告；没有把普通警告独立列为漏洞。
- Clang 22.1.4 首次语法检查因工具链补充头文件 mm_malloc.h 搜索路径缺失失败；补入本地 GCC include 路径后两份核心源文件 C11 语法检查通过。这不是 Clang 链接或运行验证。
- 两个定向验证程序以 C 源码经编译器标准输入构建，没有保存测试源文件或修改项目源码。产物为 `build/audit-review.exe`、`build/audit-boundaries.exe`。容量边界/失败注入/接力结果/关闭部分失败/席位截断/外部存储初始化/根计数边界的运行结果分别写入上述条目。失败注入只在验证翻译单元中替换 calloc，用于稳定触发真实实现的失败分支。

完成初稿后逐项回查了报告中的原代码位置、触发前提及修复语义：模式位采用 0 表示共享/阻断属于明示约定，未误报为位运算颠倒；正常菱形继承通过 ACS 避免重复访问，未误报为重复初始化；OBS 接力本来允许忽略结果，与第 5、6 项的 SBO 返回约定分别核对。第 1、4、11 项仅做静态验证，其余条目有相应定向运行证据。报告中的修复建议未编译验证，也未应用到项目。
