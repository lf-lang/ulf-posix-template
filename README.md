# micro-LF POSIX Template

![Header](https://micro-lf.org/assets/header/posix.svg)

- **micro-LF documentation:** <https://micro-lf.org>

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
    ├── HelloPosix.ulf        # Hello world example
    ├── Timer.ulf             # Timer example
    └── FederatedConnection.ulf  # Federated example
```

## Adding New Examples

To add a new micro-LF program:

1. Create a new `.ulf` file under `src/`;
1. Build it with `cmake -Bbuild -DLF_MAIN=<YourProgram> && cmake --build build`

This will create an executable `build/<YourProgram>`.

## 4. Federated Programs

A federated program consists of multiple federates that execute as separate
processes and communicate over the network. Each federate is built
and run independently. The `FederatedConnection.ulf` example defines two
federates, `r1` and `r2`, that exchange messages.

### 4.1. Build

Use `-DFEDERATE=<federate>` to select which federate to compile. Build each
federate separately, using a distinct build directory to avoid stale artifacts:

```bash
cmake -Bbuild -DLF_MAIN=FederatedConnection -DFEDERATE=r1
cmake --build build

cmake -Bbuild -DLF_MAIN=FederatedConnection -DFEDERATE=r2
cmake --build build
```

This produces two executables: `build/FederatedConnection_r1` and
`build/FederatedConnection_r2`.

### 4.2. Run

Launch each federate in its own terminal so they can communicate:

```bash
# Terminal 1
./build/FederatedConnection_r1

# Terminal 2
./build/FederatedConnection_r2
```

## 5. Formatting

To get compliant code formatting, install and run:

```bash
pip install cmakelang==0.6.13
cmake-format -i CMakeLists.txt
```

## Utilities

This template includes some useful utility functions together with examples showing how to use them:

* [initialize_from_file](util/initialize_from_file.h): A collection of C functions for initializing parameters, state variables, and local variables from a file, typically a CSV file. This is particularly useful for banks of reactors. An example is given in [BankInitialization.ulf](src/BankInitialization.ulf), which reads values from the file [BankInitializationParams.csv](src/BankInitializationParams.csv). Compile and run this as follows:

```bash
cmake -Bbuild -DLF_MAIN=BankInitialization && cmake --build build
build/BankInitialization
```

* [MuJoCo](https://mujoco.org): A physics-based simulator. This is not tested yet, but if you have a federated program where one of the federates uses MuJoCo, something like the following should work the CMakeLists.txt file:

```cmake
if(${LF_MAIN_TARGET} EQUAL "MyMujocoFed")
  find_package(mujoco 2.3.7 REQUIRED PATHS ${MUJOCO_FOLDER} NO_DEFAULT_PATH)
  target_link_libraries(${LF_MAIN_TARGET} PUBLIC mujoco::mujoco)
endif()
```

