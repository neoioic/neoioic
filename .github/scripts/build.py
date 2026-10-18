"""Build the independent xmake projects using the CI compiler and mode."""

import os
from pathlib import Path
import shutil
import subprocess
import zipfile


ROOT = Path(__file__).resolve().parents[2]


def run(*args, cwd=ROOT, capture=False):
    print('+', ' '.join(map(str, args)), flush=True)
    result = subprocess.run(list(map(str, args)), cwd=cwd, check=True,
                            text=True, stdout=subprocess.PIPE if capture else None)
    return result.stdout


def check_static(binary, windows):
    if windows:
        imports = run('objdump', '-p', binary, capture=True).lower()
        # Windows system DLLs remain OS dependencies even with static runtimes.
        for runtime in ('libgcc', 'libstdc++', 'libwinpthread', 'libc++',
                        'libunwind', 'clang_rt'):
            if any(runtime in line for line in imports.splitlines()
                   if 'dll name:' in line):
                raise RuntimeError(f'{binary} imports a dynamic compiler runtime')
    else:
        headers = run('readelf', '-l', binary, capture=True)
        dynamic = run('readelf', '-d', binary, capture=True)
        if 'INTERP' in headers or '(NEEDED)' in dynamic:
            raise RuntimeError(f'{binary} is not statically linked')


def main():
    os.chdir(ROOT)
    compiler = os.environ['CI_COMPILER']
    mode = os.environ['CI_MODE']
    if compiler not in ('gcc', 'clang') or mode not in ('debug', 'release'):
        raise ValueError('Unsupported compiler or build mode')
    windows = os.name == 'nt'
    platform = 'mingw' if windows else 'linux'
    cxx = 'g++' if compiler == 'gcc' else 'clang++'
    options = ['-p', platform, '-a', 'x86_64', '-m', mode,
               f'--cc={compiler}', f'--cxx={cxx}', f'--ld={cxx}',
               '--ldflags=-static', '--policies=build.ccache:n', '-y']
    if windows:
        gcc = shutil.which('gcc')
        if not gcc:
            raise RuntimeError('MinGW GCC not found')
        options += [f'--mingw={Path(gcc).resolve().parent.parent}']
    else:
        options += [f'--toolchain={compiler}']

    examples = ['hello_world', 'single_inheritance', 'multiple_inheritance']
    if windows:
        examples.append('wgi')
    projects = [('.', None), ('tests', None)]
    projects += [(f'examples/{name}', name) for name in examples]
    binaries = []
    for project, target in projects:
        directory = ROOT / project
        run('xmake', 'f', '-P', '.', *options, cwd=directory)
        run('xmake', '-P', '.', '-r', cwd=directory)
        output = directory / 'build' / platform / 'x86_64' / mode
        names = [target] if target else (['robustness', 'dispatch'] if project == 'tests' else [])
        for name in names:
            binary = output / (name + ('.exe' if windows else ''))
            check_static(binary, windows)
            binaries.append((project, binary))
        if mode == 'debug':
            if project == 'tests':
                run('xmake', 'test', '-P', '.', '-v', cwd=directory)
            elif target and target != 'wgi':
                run('xmake', 'run', '-P', '.', target, cwd=directory)

    if compiler != 'gcc' or mode != 'release':
        return
    packages = ROOT / 'build' / 'packages'
    packages.mkdir(parents=True, exist_ok=True)
    system = 'windows' if windows else 'linux'
    archive = packages / f'neoioic-x86_64-{system}.zip'
    with zipfile.ZipFile(archive, 'w', zipfile.ZIP_DEFLATED) as package:
        for project, binary in binaries:
            package.write(binary, f'{project}/{binary.name}')
        core = ROOT / 'build' / platform / 'x86_64' / mode / 'libneoioic.a'
        package.write(core, 'lib/libneoioic.a')
        for header in sorted((ROOT / 'include').glob('*.h')):
            package.write(header, f'include/{header.name}')
        for document in ('LICENSE', 'README.md', 'docs/build.md',
                         'tests/README.md', 'docs/coding_style.md',
                         'docs/architecture.md', 'docs/tutorial.md', 'docs/handoff.md'):
            package.write(ROOT / document, document)
        if windows:
            for resource in sorted((ROOT / 'examples/wgi/skins').rglob('*')):
                if resource.is_file():
                    package.write(resource, resource.relative_to(ROOT))
        package.writestr('BUILD.txt', f'Commit: {os.environ.get("GITHUB_SHA", "local")}\n'
                         f'Compiler: {run(compiler, "--version", capture=True)}')
    print(f'Packaged {archive}', flush=True)


if __name__ == '__main__':
    main()
