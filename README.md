# Thesis Monorepo

This repository is the monorepo for all work regarding my bachelor's thesis.

The thesis is about extending the ARM32 ISA with instructions to accelerate the execution of WebAssembly. Similar to prior extensions aiming to accelerate the execution of Java Bytecode.

### Toolchain

- **Walrus**: WebAssembly Lightweight RUntime (S), a lightweight WASM runtime engine
- **SLJIT**: A low-level, platform-independent JIT compiler
- **emscripten**: C/C++ to WASM compiler
- **QEMU**: Emulator for emulating an ARM32 processor

### Getting Started

1. Clone the repository

```console
$ git clone --recursive-submodules https://github.com/eyeonspringfield/thesis-monorepo
$ cd thesis-monorepo/walrus
$ git checkout thesis-mods
$ cd ..
```

2. Install emscripten

```console
$ cd toolchain/emsdk
$ ./emsdk install latest
$ ./emsdk activate latest
$ cd ../..
```

3. Compile Walrus for ARM32

```console
$ cd walrus
$ cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -H. -Bout/release/arm -DWALRUS_ARCH=arm -DWALRUS_HOST=linux -DWALRUS_MODE=release -DWALRUS_OUTPUT=shell -DCMAKE_C_COMPILER=arm-linux-gnueabi-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabi-g++ -DCMAKE_EXE_LINKER_FLAGS="-static" -GNinja
$ ninja -Cout/release/arm
```

4. Compile the C and C++ programs in the `src` folder to WASM

```console
$ cd ..
$ make
```

Or compile individual files manually:

```console
$ source toolchain/emsdk/emsdk_env.sh && toolchain/emsdk/upstream/emscripten/emcc src/main.c -O2 -s STANDALONE_WASM -s WASM_BIGINT=0 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -o build/main.wasm
```

5. Run the compiled WASM programs using Walrus and QEMU

```console
$ make run
```

Or run individual files manually:

```console
$ mkdir -p logs
$ qemu-arm -d in_asm -D logs/main.log ./walrus/out/release/arm/walrus --jit build/main.wasm
```

The log files in the `logs` folder will contain the instructions executed by Walrus for each program.

### Required tools
- CMake
- GNU Make
- Ninja
- QEMU
- arm-linux-gnueabi-gcc & arm-linux-gnueabi-g++
- gcc-arm-linux-gnueabihf & g++-arm-linux-gnueabihf

To install the required tools on Debian, run:

```console
# apt install cmake make ninja-build qemu-system qemu-user arm-linux-gnueabi-gcc arm-linux-gnueabi-g++ gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
```