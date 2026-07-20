# micro-LF POSIX Template

![Header](https://micro-lf.org/assets/header/posix.svg)

- **Documentation:** <https://micro-lf.org>

______________________________________________________________________

This is a template for micro-LF applications targeting POSIX platforms (Linux and macOS).

## 1. Prerequisites

### 1.1. Basic

- A C compiler (GCC or Clang)
- CMake ≥ 3.20
- Set required environment variables:
  - `REACTOR_UC_PATH` — Path to reactor-uc repository

### 1.2. micro-LF

This template is for running micro-LF applications on POSIX platforms. It uses
[reactor-uc](https://github.com/lf-lang/reactor-uc), the runtime that facilitates the execution. Clone
this repo with one of the following commands:

#### Clone via HTTPS

```bash
git clone https://github.com/lf-lang/reactor-uc.git --recurse-submodules
```

#### Or Clone via SSH

```bash
git clone git@github.com:lf-lang/reactor-uc.git --recurse-submodules
```

And make sure that the `REACTOR_UC_PATH` environment variable is pointing to it.

## 2. Build Your Project

By default, in this template, the build compiles `src/HelloPosix.ulf` when you issue the following commands:

```bash
mkdir build && cd build
cmake ..
make
```

Alternatively, use CMake presets:

```bash
cmake --preset release
cmake --build --preset release
```

The first command generates code without compiling it.
The second command generates code and compiles it, creating the binary executable `build/HelloPosix`.

In VSCode or Cursor, the Build command (`CMake Build`) will generate code and compile it. `CMake Configure` will generate code without compiling it.

## 3. Run Your Application

```bash
./build/HelloPosix
```

## Project Structure

```
ulf-posix-template/
├── CMakeLists.txt         # Main CMake configuration
├── CMakePresets.json      # CMake preset configurations
├── README.md              # This file
└── src/                   # micro-LF source files
    ├── HelloPosix.ulf     # Hello world example
    └── Timer.ulf          # Timer example
```

## Adding New Examples

To add a new micro-LF program:

1. Create a new `.ulf` file under `src/`;
1. Build it with `cmake -Bbuild -DLF_MAIN=<YourProgram> && cmake --build build`

This will create an executable `build/<YourProgram>`.
