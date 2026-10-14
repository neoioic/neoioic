# 构建与验证

## 独立项目

| 项目路径 | 目标 | 平台 |
| --- | --- | --- |
| 仓库根目录 | `oioic` 静态库 | GCC/Clang 的 C11 工具链 |
| `examples/hello_world` | `hello_world` | 控制台 |
| `examples/single_inheritance` | `single_inheritance` | 控制台 |
| `examples/multiple_inheritance` | `multiple_inheritance` | 控制台 |
| `examples/wgi` | `wgi` | Windows / MinGW-w64 |

每个示例有独立配置与输出目录，通过 `../../src` 引用核心库定义，不依赖先构建根目录，也不依赖其他示例。使用 xmake 是为了统一 C 编译、静态库依赖、Windows 资源编译及资源部署，同时保留独立入口。

## Windows GCC

安装 xmake 与完整 MinGW-w64，将工具链 `bin` 目录加入 PATH，或明确指定 `--mingw`。请填写自己机器的工具链路径，不要把示例路径照搬到其他环境。

在任意项目目录执行：

```powershell
xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -a x86_64 -m debug
xmake -P .
```

运行控制台示例：`xmake run -P . <目标名>`。构建 WGI 还需要工具链自带的 `windres`；xmake 会编译 `wgidemo.rc`，链接 `user32`、`gdi32`、`ole32`、`oleaut32`、`uuid`，并将 `skins/` 复制到可执行文件旁。移动 WGI 时必须一起移动该资源目录。

切换优化构建时再次明确平台与工具链，例如 `xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -m release`，然后重新构建。xmake 重新配置时可能重新选择默认平台，不能假定仅传 `-m release` 会保留 MinGW 配置。清理当前项目：`xmake clean -P .`。完整重建使用 `xmake -P . -r`。

## GCC/Clang 与其他系统

Linux/macOS 的核心库、控制台示例：

```sh
cd examples/multiple_inheritance
xmake f -P . --toolchain=gcc -m debug
xmake -P .
xmake run -P . multiple_inheritance
```

Clang 将工具链替换为 `clang`。Windows 使用 Clang 时，需要完整的 Windows/MinGW 头文件、库和资源工具，并使 xmake 选择匹配的工具链；仅有一个 `clang.exe` 不保证具备这些依赖。当前工作区的运行验证以 GCC 为准。

## 验证范围

以下是已有验证记录，不是每次文档更新时重新执行的结果。迁移阶段使用 Windows x86_64、MinGW-w64 GCC 15.1、xmake 2.9.6。核心库与四个示例分别配置 Debug/Release 并编译，三个控制台示例在两种配置下运行并核对输出。多继承示例输出汽车、船和两栖车的重量、载重及速度。核心源码另通过 Clang 22.1.4 的 C11 语法检查，使用本地 MinGW 系统头文件与 GCC 的补充头文件路径；这不等于 Clang 全量链接验证。

Linux 风格重写后再次分别重构建上述五个项目的 Debug/Release，构建通过。三个控制台示例的六次运行输出与重写前完全一致。88 个 C 源码及头文件通过 clang-format 检查；排除命名、类型写法、注释与排版差异后的词法序列保持一致，用于核对架构和算法未被改写。核心的 Clang C11 语法检查也已重新通过。

迁移阶段 WGI 已检查皮肤资源部署、窗口启动及正常关闭，退出码为 0；菜单、编辑及所有控件交互未做完整回归。Linux/macOS 原生运行以及 Clang 全量构建尚不能由上述 GCC 结果推断。

2026-10-11 核心问题修复后，使用上述 MinGW 工具链分别编译核心与四个示例的 Debug/Release，三个控制台示例在两种配置下运行通过。本次 WGI 仅验证编译链接，没有执行窗口交互回归。临时定向验证程序保存在本地 `build/`，分别以开启断言的 Debug 和 `-O2 -DNDEBUG` 编译运行，覆盖容量 0～17 的 18 万次队列混合操作、扩容分配失败与参数位于旧队列的情况、短输出/输入和未对齐字节流、七类 SBO 接力返回值、部分关闭及嵌套传播/重试、打开失败后的清理失败、根节点引用边界、构造席位上限、非零填充外部存储和动态/外部存储的 OID 耗尽清理。分配失败通过链接器 `--wrap=calloc` 注入，不修改生产源码。

`build/` 被 Git 忽略，以上临时程序不是受版本管理的测试套件，新克隆不包含它们。没有配置统一测试目标或自动回归流程。需要复现定向检查时，应在当前工作区核对测试源文件是否存在，并从当前源码重新编译，不能以旧可执行文件运行成功代替验证。交接入口及本地复现命令见[交接指南](handoff.md)。

## 迁移说明

- 将核心和示例中重复的核心副本合并为一份。
- 教学示例直接替换旧 `IRESULT`/`FRESULT` API，统一使用 `int` 及当前结果域。
- 清除 VC6 工程、中间产物、缓存、旧版本目录和已展开压缩包。
- 活跃源码采用 UTF-8、C11；修正构造布局对齐和 Windows 64 位指针接口。
- 源码按[Linux 风格](coding-style.md)整理：小写下划线命名、显式结构体类型、8 列 Tab 缩进。API 的具体名称同步公共头文件、示例和当前文档，历史教材保留原始名称。
- `oicc` 只保留作者的工具二进制，不作为可重建项目或编译步骤。
