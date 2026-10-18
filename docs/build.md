# 构建与验证

## 独立项目

| 项目路径 | 目标 | 平台 |
| --- | --- | --- |
| `tests` | `robustness`、`dispatch` | GCC / GNU ld（含 MinGW） |
| 仓库根目录 | `neoioic` 静态库 | GCC/Clang 的 C11 工具链 |
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

运行控制台示例：`xmake run -P . <目标名>`。构建 WGI 还需要工具链自带的 `windres`；xmake 会编译 `wgi_demo.rc`，链接 `user32`、`gdi32`、`ole32`、`oleaut32`、`uuid`，并将 `skins/` 复制到可执行文件旁。移动 WGI 时必须一起移动该资源目录。

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

## 健壮性测试

受版本管理的独立测试项目位于 `tests/`，不依赖旧的 `build/` 临时程序。先配置测试项目，再构建并运行：

```powershell
xmake f -P tests -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P tests
xmake test -P tests -v
```

将配置改为 `-m release` 后重新构建并运行，测试检查在 `NDEBUG` 下仍有效。完整命令、用例范围及 GNU 链接器要求见 [测试说明](../tests/README.md)。2026-10-15 两个测试目标已在上述 Windows/MinGW 工具链下分别通过 Debug/Release 构建与运行；未执行 WGI 交互或 Linux/macOS 运行验证。

## GitHub Actions 与 Nightly

[Nightly 工作流](../.github/workflows/nightly.yml) 在分支 push、Pull Request 和手动触发时运行 Windows/Ubuntu x86_64 × GCC/Clang × Debug/Release 八项构建。各项目保持独立的 xmake 构建入口，CI 使用 `-static` 链接；Linux 检查 ELF 无动态解释器和共享库依赖，Windows 检查不依赖编译器运行时 DLL（系统 DLL 仍由 Windows 提供）。Windows 使用 MSYS2 UCRT64 的 GCC、Clang 和资源编译器。

构建任务按 `mingw / gcc / debug`、`linux / clang / debug` 等格式显示平台、编译器和模式；实际 runner 仍为 Windows/Ubuntu。每种 Debug 配置均运行 `tests` 的两个目标及三个控制台示例；WGI 仅在 Windows 编译，不在 CI 自动打开窗口。所有八项任务成功后，默认分支的 push 才会更新固定 `nightly` 标签及名为 `Nightly` 的预发行版。第一次创建发行版，以后更新标签指向、提交说明，并覆盖两个同名附件，不新建发行版，也不将其标为 Latest：

- `neoioic-x86_64-windows.zip`
- `neoioic-x86_64-linux.zip`

压缩包只使用对应系统的 GCC Release 结果，包含示例可执行文件、测试可执行文件、核心静态库、公共头文件、许可证和说明。Windows 包额外包含 WGI 与 `skins/`；解压后在 WGI 所在目录运行以读取皮肤。`BUILD.txt` 记录提交及 GCC 版本。Clang Release 用于构建检查，不发布。其他分支、Pull Request 和手动运行只验证，不覆盖 Nightly。

发行任务使用仓库自带的 `GITHUB_TOKEN` 和任务级 `contents: write`，不需要额外令牌。构建任务仅有只读权限。若仓库的标签规则限制移动 `nightly`，须允许该自动发行操作。同一分支的新运行会取消旧运行。

构建与打包逻辑位于 [CI 脚本](../.github/scripts/build.py)，本地也可设置 `CI_COMPILER=gcc` 或 `clang`、`CI_MODE=debug` 或 `release` 后执行。2026-10-15 本地 Windows GCC Debug/Release 均完成全量构建与运行时依赖检查，Debug 测试和控制台示例通过，Release zip 完成生成及完整性检查；其他矩阵组合与 GitHub 发行操作须以实际 Actions 运行结果为准。

## Wiki 自动发布

独立工作流 `.github/workflows/wiki.yml` 在默认分支 push 时发布 `docs/wiki.md`，也支持在默认分支手动运行。它读取 push 前的文档，并与 Wiki 最新已发布快照核对；内容相同不会新增页面。尚无快照时，即使本次没有修改文档，也会发布当前文档，因此启用功能不需要人为修改教程。之前发布失败时，后续运行也会补发尚未同步的内容。

页面名为 `NEOioic Wiki (YYYYMMDD)`，当天第二次及以后为 `NEOioic Wiki (YYYYMMDD_2)`、`NEOioic Wiki (YYYYMMDD_3)`，历史页面保持原样。日期使用 push 时间并按 Asia/Shanghai 时区计算，手动运行使用当前时间。序号从 Wiki 已有页面中计算，不依赖 Actions 缓存；重复运行相同内容不会重复发布。此任务与 Nightly 构建独立串行发布，不受构建失败影响。

首次配置需要在仓库 Settings 中启用 Wiki，并在 GitHub Wiki 页面创建一次初始页面（例如 Home）；GitHub 不支持通过 Git push 创建尚未初始化的 Wiki 仓库。初始页不需要放教程内容。随后添加仓库 Actions secret `WIKI_TOKEN`，使用有该仓库 Wiki 写入权限的令牌（classic PAT 对公开仓库使用 `public_repo`，私有仓库使用 `repo`，组织仓库还需满足其授权策略）；默认 `GITHUB_TOKEN` 不支持推送 Wiki。完成后推送或手动运行工作流即可生成首篇教程版本。若尚未配置，任务会给出初始化提示，完成配置后重跑即可。令牌仅用于 Git 认证，不写入远程地址或 Git 配置文件。

若 Wiki 任务提示 `WIKI_TOKEN` 缺失或为空，表示尚未获得发布凭据，并非文档或 Git 差异有错。到仓库 **Settings → Secrets and variables → Actions → New repository secret** 添加 `WIKI_TOKEN`（不是 Actions variable）。使用专用 classic PAT：公开仓库选 `public_repo`，私有仓库选 `repo`，令牌所属账户必须有仓库写权限。组织 secret 还需允许本仓库访问。保存后在 Actions 重跑 Wiki 工作流，无需再次修改教程。脚本会在执行 Git 操作前检查凭据，并将缺失配置的修复步骤写入任务摘要；缺少凭据仍标记失败，不会把未发布误报为成功。

## 迁移说明

- 将核心和示例中重复的核心副本合并为一份。
- 教学示例直接替换旧 `IRESULT`/`FRESULT` API，统一使用 `int` 及当前结果域。
- 清除 VC6 工程、中间产物、缓存、旧版本目录和已展开压缩包。
- 活跃源码采用 UTF-8、C11；修正构造布局对齐和 Windows 64 位指针接口。
- 源码按[Linux 风格](coding_style.md)整理：小写下划线命名、显式结构体类型、8 列 Tab 缩进。API 的具体名称同步公共头文件、示例和当前文档，历史教材保留原始名称。
- `oicc` 只保留预编译二进制，不作为可重建项目或编译步骤。
