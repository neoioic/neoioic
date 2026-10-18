# 健壮性回归测试

本目录是受版本管理的独立 xmake 项目，不改变根目录只构建静态库的约定。需要 C11、xmake 2.9.6 或更新版本，以及支持 GNU ld `--wrap` 的 GCC/MinGW 工具链；当前未验证 MSVC、Apple 链接器或其他链接器。

从仓库根目录运行（替换本机工具链路径）：

```powershell
xmake f -P tests -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P tests
xmake test -P tests -v
xmake f -P tests -p mingw --mingw="D:/path/to/mingw64" -m release
xmake -P tests
xmake test -P tests -v
```

Linux GCC 可使用 `xmake f -P tests --toolchain=gcc -m debug`，随后执行相同的构建、测试命令；Release 单独配置。此处是使用说明，不代表已在 Linux 上执行验证。

测试失败会输出源文件、行号和条件，并以非零状态退出。所有测试动作与检查均使用 `CHECK`，不会随 `NDEBUG` 消失。队列随机序列使用固定种子，可重复复现。

| 目标 | 检查范围 |
| --- | --- |
| `robustness` | 容量 0～17、18 万次队列操作，与独立顺序缓冲模型逐步对比；批量与单字节宏混用、环绕、满空、丢失标记、零长度入列、输出缓冲区边界 |
| `robustness` | 根节点引用上限/下限、双队列容量命令的短流/超长流/空指针及未对齐流、容量参数位于待替换队列、分配失败保留原数据、禁用队列、重置与模式位 |
| `robustness` | 部分关闭、重复失败、访问席位耗尽、嵌套传播与重试、打开失败后的清理失败 |
| `robustness` | 三种示例对象的动态/外部存储逐次分配失败、恢复创建、布局对齐、非零外部内存初始化、席位上限、OID 耗尽、OID 复用、回收表首次分配及扩容失败后重试 |
| `robustness` | 菱形继承共享节点、重复打开/关闭的引用计数、非共享模式拒绝打开、ACS 清理、相同调用者切换委托者与重复访问拒绝 |
| `dispatch` | 七类 SBO 接力接口在零/单/双基节点及五种返回码下的结果；访问席位耗尽、输出数量初始化、重复基节点去重和 ACS 清理 |

`robustness.c` 为测试内部边界直接包含根接口和多继承示例宿主实现，因此目标不重复链接 `src/neoioic.c` 或示例 `host.c`。其余核心和示例节点始终从当前源码编译。`dispatch` 使用正常核心静态库依赖。

分配失败通过链接器包装 `calloc` 注入，第 N 次分配失败后自动恢复。包装 `free` 追踪被包装 `calloc` 返回的存储，在失败路径及测试结束核对未释放数量；外部构造区由测试单独分配释放。这是定向资源检查，不等同于通用内存检测器，也不覆盖并发、非法调用者存储或 WGI 图形交互。

2026-10-15 在 Windows x86_64、MinGW-w64 GCC 15.1、xmake 2.9.6 下，两个目标均完成 Debug 和 Release 构建与运行。Release 明确启用 `NDEBUG`，验证错误检查不依赖生产断言。
