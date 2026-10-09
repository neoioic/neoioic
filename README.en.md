# OIOIC

OIOIC is a C object model and construction tool designed by Zhao Pingzhi. Its name comes from Open, Input, Output, Interact and Close. Structures hold object state, function pointers implement interfaces, and node graphs represent single and multiple inheritance.

This repository consolidates the 1.0.18 runtime into a shared C11 library. Every example has its own xmake project and builds independently. Sources use UTF-8; Git manages versions.

## Layout

| Directory | Purpose |
| --- | --- |
| `include/`, `src/` | Public headers and shared runtime |
| `examples/hello_world/` | Minimal console application |
| `examples/single_inheritance/` | Vehicle and car inheritance |
| `examples/multiple_inheritance/` | Car, ship and amphibious vehicle; shared base nodes |
| `examples/wgi/` | Windows GUI, controls and image skins |
| `docs/` | Current guides and historical Chinese/English primers |
| `tools/oicc/` | Original prebuilt constructor binaries; no tool source is supplied |

## Build

Install xmake and GCC or Clang. Windows builds use a complete MinGW-w64 toolchain, including its resource compiler.

```powershell
# Core library only, from the repository root
xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P .

# An independent example
cd examples/multiple_inheritance
xmake f -P . -p mingw --mingw="D:/path/to/mingw64" -m debug
xmake -P .
xmake run -P . multiple_inheritance
```

The other example target names are `hello_world`, `single_inheritance`, and `wgi`. Each example compiles the shared core in its own build directory. Root builds never build examples. Use `-P .` to explicitly select the current project.

On Linux/macOS, configure the library and console examples with `xmake f -P . --toolchain=gcc -m debug`, or `--toolchain=clang`. WGI requires Windows APIs and is not a portable GUI framework. Native non-Windows builds have not been verified in this Windows workspace.

The constructor binaries are optional and are not executed by the build. Their generated code must be reviewed for the current API and alignment requirements. Caller records identify access contexts; they do not replace thread synchronization.

Local build verification uses MinGW-w64 GCC 15.1 and xmake. The three console examples were executed. See the Chinese [build guide](docs/build.md), [architecture guide](docs/architecture.md), and [tutorial](docs/tutorial.md) for details. The original English primer is available at [docs/primer/en/Index.htm](docs/primer/en/Index.htm); its old API and VC6 instructions are historical references.

## License

See [LICENSE](LICENSE), AGPL-3.0. Historical author notices are retained. The author's original README also requests attribution to OIOIC when publishing derivative innovations or papers.
