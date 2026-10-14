# OIOIC Agent 指南

## 背景与入口

OIOIC（道智编程）由赵平智设计，是以 C 实现的对象模型与构造工具；名称来自 Open、Input、Output、Interact、Close。本仓库以 1.0.18 为核心，教学示例已迁移到统一 API；历史教程 1.0.6 不代表当前可编译 API。

先读 `README.md`、`docs/handoff.md`、`docs/architecture.md`、`docs/build.md`、`docs/tutorial.md`，再读 `include/o.h`、`include/oioic.h`、`src/o.c`、`src/oioic.c`。交接文档记录当前状态与验证边界；源码和构建定义是行为依据。

## 模块与构建

- `include/` 是公共头文件，`src/` 是共享运行时。根 `xmake.lua` 只构建 `oioic` 静态库。
- `examples/hello_world`、`single_inheritance`、`multiple_inheritance`、`wgi` 各有独立 `xmake.lua`、配置及输出目录。每个示例引用 `../../src`，不能把示例目标集中塞进根构建。
- 应用宿主 `ho.c` 提供 `host_create_object`、`host_destroy_object`、oid 管理与业务对象创建选择。应用入口在 `so/ao/Main/Main.c`，一般对象在 `so/go`，辅助功能在 `se`。
- 使用 C11、UTF-8，GCC/Clang 方向；WGI 特定依赖 Win32/GDI/OLE，不能宣称其跨平台。
- Windows 实测工具链为 MinGW-w64 GCC 15.1、xmake 2.9.6。在每个项目目录使用 `xmake f -P . -p mingw --mingw="工具链路径" -m debug`、`xmake -P .`；`-P .` 防止命中之前记住的根项目。
- `tools/oicc/` 仅保留上游预编译二进制，没有源码，不在构建时自动调用。详细限制见其 README。
- `docs/primer/zh` 是中文历史教材，旧 API/VC6 截图只能作为资料。文档仅保留中文版本。压缩包、核心副本、旧 WGI 版本和 VC 产物已在迁移阶段清理，版本应交给 Git 管理。

## 架构约束

- `struct object` 表示节点，`model_id` 标识对象模，`oid` 标识对象，`struct em_xxx` 是节点自有状态。
- AND 首项是最终派生节点；AIB 是直接基节点，ABN 是全部基节点，ACS 保存 `struct vr` 访问记录。根节点 OIOIC 包含队列与模式。
- `crt_xxx` 构造节点图并布置内存，`tog_xxx` 绑定接口。用 `size_t` 计算内存，扩展成员块使用 `OIOIC_ALIGNED_SIZE`；新增更严格对齐类型必须重新核对布局。
- 五类接口展开为九个函数指针。`interact0`～`interact3` 分别无流、仅输出、仅输入、输入输出。使用对应 `AC0_`～`AC3_` 扩展命令，明确数据尺寸与输出数量。
- 业务使用 `vo_*` 访问；直接调用接口会绕过访问登记。OBS 先基节点后自身，SBO 先自身后基节点；分派专用中性结果必须保留其语义。
- 使用统一 `int` 和 `RN/RO/RP`，不能重新引入 `IRESULT`/`FRESULT` 兼容别名。
- `struct vr` 的 `cr` 是调用者，`mr` 是委托者。访问记录、队列、引用计数和 OID 分配不自动保证线程安全，应用负责同步。
- 创建/打开/关闭/销毁是不同阶段；检查错误及资源释放，不要依赖 release 中被禁用的断言来执行必要业务。
- `RN_CLOSEPARTIAL` 表示已经部分关闭，保留引用仅供重试清理；不得继续业务访问、再次打开或直接销毁。打开失败后的清理也可能返回此结果。当前没有自动锁定部分关闭状态，调用者必须遵守协议。
- 空队列的 `front/rear` 为 NULL；非空时是数组内的首、尾字节地址。不要恢复 `data - 1` 哨兵。容量命令按字节流用 `memcpy` 读写整数，长度检查必须在 Release 中有效，扩容失败保留原队列。
- 构造时检查最大节点席位倍数，避免 `caller_count` 窄化；外部存储构造会清零构造区，但空间大小和对齐仍由调用者保证。外部存储对象用 `host_destroy_object` 清理，不用会释放对象本体的 `destroy_object` 宏。
- WGI 必须用 `GetWindowLongPtr`/`SetWindowLongPtr` 存放对象指针，宽字符串使用标准带容量的调用，图像及 OLE 资源明确拥有者和释放时机。
- `<ibn>` 是生成器识别的继承声明，`<crt>` 是构造代码。旧 oicc 输出需要审查 API 与对齐，不能无条件覆盖已迁移代码。

## 实现原则

活跃 C 源码遵循 [Linux 风格约定](docs/coding-style.md)：8 列 Tab、小写下划线命名、直接使用 `struct` 类型，常量与枚举项使用大写下划线。使用根 `.clang-format` 和 `.editorconfig`；保留 Win32/OLE 外部符号的规定名称。命名变更要同步调用点、构造代码及当前文档，历史教材明确标注旧 API。`caller_context` 表示访问上下文指针，局部 `caller` 记录可用于切换委托者，不能合并两者。

你应该思考让你的代码精简优化，改动小，简洁优雅，符合最佳实践。不要创建无意义的自由函数，思考尽量不要或减少新增无意义的成员变量。不要兼容旧的遗留的实现，而是删除替换旧的实现。你的实现应当有通用性与扩展性，避免硬编码与限制。消除嵌套，消除强耦合，消除一大堆扁平的函数，改用较为 oop 的设计，禁止考虑向后兼容。适当拆出变量，从而更加清晰且减少嵌套。

以对象职责和状态所有权组织代码，C 的对象接口和组合即可表达 OOP。优先提前返回、清晰局部变量和明确失败清理；不要添加可推导的持久状态或无用抽象。替换实现时同步调用点、构造代码和文档，删除失效路径，保持任务范围明确。

## 检查与许可证

构建相关变更分别编译核心与受影响示例；生命周期、继承、队列或布局变更应检查对应行为及失败路径。报告实际执行的验证，不把成功编译说成全面运行测试。

`build/` 与 `.xmake/` 被 Git 忽略；本地临时回归程序不是仓库维护的测试套件，换工作区后不能假定存在。任务以局部修复为主，未经需求支持不要改公共接口签名或扩展到无关业务。当前没有待续的 `report.md`，此前报告已修复并按要求移除。

根 `LICENSE` 当前为 MIT（提交 `aaa14ff` 更新），源码历史作者声明保留。许可说明以实际 LICENSE 为准，不要继续引用旧 AGPL-3.0 说明，也不要将历史评价或署名倡议推断为额外许可条款。
