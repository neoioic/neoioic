# OIOIC

OIOIC（道智编程）是赵平智设计的 C 语言对象模型及构造工具。名称来自 Open、Input、Output、Interact、Close 五类统一接口。对象通过结构体保存状态、函数指针实现接口，并使用继承节点图支持单继承和多继承。

本仓库基于 OIOIC 1.0.18 整理为 C11 项目：核心源码集中维护，教学示例统一使用当前 API，每个项目具有独立的 xmake 构建入口。源码采用 UTF-8，版本由 Git 管理。

[构建指南](docs/build.md) · [架构说明](docs/architecture.md) · [开发教程](docs/tutorial.md) · [代码风格](docs/coding-style.md)

活跃源码采用 Linux 风格的小写下划线命名、8 列 Tab 缩进和直接可见的结构体类型，例如 `struct object`、`vo_open`、`get_base_members`。当前名称以公共头文件为准，旧 API 名称不提供兼容别名。核心边界及失败处理已修正，关闭失败的清理约定见[架构说明](docs/architecture.md)。

## 目录

```text
include/                      公共头文件 o.h、oioic.h
src/                          核心运行时与可复用库构建定义
examples/hello_world/         最小控制台程序，独立构建
examples/single_inheritance/  vehicle -> car，独立构建
examples/multiple_inheritance/ vehicle -> car/ship -> amphicar，独立构建
examples/wgi/                 Windows GUI、控件与皮肤，独立构建
docs/                        架构、构建、教程与历史教材
tools/oicc/                  作者提供的预编译构造工具
xmake.lua                    仅构建核心静态库
```

示例引用 `src/xmake.lua` 和公共头文件，分别在自己的 `build/`、`.xmake/` 中管理构建产物与配置。核心库不依赖示例，构建某个示例也不会构建其他示例。运行时核心中的 `create_object`/`destroy_object` 约定由应用宿主的 `ho.c` 实现。

## 快速构建

需要 xmake、GCC（Windows 使用 MinGW-w64）或 Clang。Windows 下推荐使用 GCC 的完整 MinGW 工具链，包含 `ar`、`windres` 等工具。

在 PowerShell 中构建核心库：

```powershell
xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P .
```

独立构建和运行示例：

```powershell
cd examples/multiple_inheritance
xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P .
xmake run -P . multiple_inheritance
```

其他示例用相同流程，目标分别为 `hello_world`、`single_inheritance`、`wgi`。`-P .` 明确指定当前项目，避免 xmake 使用之前记住的根目录项目。

Linux/macOS 的核心库和控制台示例可以配置 `xmake f -P . --toolchain=gcc -m debug`；Clang 使用 `--toolchain=clang`。WGI 使用 Win32/GDI/OLE，只适用于 Windows 或 MinGW 交叉编译，不是跨平台 GUI。

## 能力与示例

- 统一的打开、数据输入输出、行为交互与关闭接口。
- 节点自己的扩展成员 `struct em_xxx`，以及共享基节点的多继承对象图。
- `struct vr` 调用者上下文和访问登记；并发同步仍由应用负责。
- WGI 展示带皮肤的窗口、按钮、菜单、编辑框及滚动条。

可基于这些对象设计设备模拟器、数据流管线、继承关系可视化工具或 Windows 桌面应用。这里没有额外的语言编译器；`oicc` 生成 C 节点与构造代码，最终由 C 编译器编译。

## 工具与历史

`tools/oicc/windows/oicc.exe` 和 `tools/oicc/linux/oicc` 是上游提供的 1.0.18 二进制，仓库未提供其源码，因此不能从本仓库用 GCC 重建。它们不参与任何构建，也不在构建时自动执行。旧工具生成的构造代码需要按当前内存对齐与 API 约定审查，见 [工具说明](tools/oicc/README.md)。

项目 2007 年公开对象模型，2008 年托管于 Google Code，2009 年发布第二版教程，2011 年发布 1.0.18，2026 年在 Gitee/GitHub 重新发布。中文历史教材保留在 `docs/primer/zh/`，其中旧 API 与 VC6 操作步骤仅供历史参考；当前开发以本 README 和 Markdown 文档为准。

## 验证与许可

本地使用 MinGW-w64 GCC 15.1 与 xmake 构建核心库及四个独立示例，Linux 风格重写后的 Debug/Release 均通过重构建。三个控制台示例的输出与重写前一致；WGI 窗口启动、正常关闭检查通过。详细验证范围见 [构建指南](docs/build.md)。

仓库许可证见 [LICENSE](LICENSE)（AGPL-3.0），源码保留作者版权声明。README 原有声明要求基于 OIOIC 的创新代码或论文说明其原创基础。
