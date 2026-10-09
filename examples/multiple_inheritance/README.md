# multiple_inheritance

汽车与船共享 vehicle，两栖车展示菱形多继承与基节点状态共享。

这是独立的 xmake 项目，引用仓库共享核心，不依赖预先构建根项目或其他示例。

在本目录使用 MinGW-w64 GCC：

```powershell
xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P .
xmake run -P . multiple_inheritance
```

Linux/macOS 可以配置 `xmake f -P . --toolchain=gcc -m debug`，Clang 使用 `--toolchain=clang`。

构建产物位于本项目的 build/；程序入口在 so/ao/Main/Main.c，应用宿主在 ho.c，业务对象在 so/go/。

[构建指南](../../docs/build.md) · [架构](../../docs/architecture.md) · [教程](../../docs/tutorial.md)
