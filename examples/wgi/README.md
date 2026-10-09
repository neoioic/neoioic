# wgi

Windows 皮肤界面示例，包含按钮、菜单、编辑框及滚动条。

这是独立的 xmake 项目，引用仓库共享核心，不依赖预先构建根项目或其他示例。

在本目录使用 MinGW-w64 GCC：

```powershell
xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P .
xmake run -P . wgi
```

WGI 需要 Windows API、GDI、OLE 和 windres。构建会把 skins/ 复制到程序旁，发布时必须保留该目录。

构建产物位于本项目的 build/；程序入口在 so/ao/Main/Main.c，应用宿主在 ho.c，业务对象在 so/go/。

[构建指南](../../docs/build.md) · [架构](../../docs/architecture.md) · [教程](../../docs/tutorial.md)
