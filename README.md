# Thesis Monorepo

This repository is the monorepo for all work regarding my bachelor's thesis.

### Toolchain

- **Walrus**: WebAssembly Lightweight RUntime (S), a lightweight WASM runtime engine
- **SLJIT**: A low-level, platform-independent JIT compiler
- **emscripten**: C/C++ to WASM compiler
- **QEMU**: Emulator for emulating an ARM32 processor

### Getting Started

> To skip steps 1–4, you can run:
> ```console
> $ ./setup.sh
> ```
> from the repository root. This installs Emscripten, compiles wasm2wat and compiles Walrus for ARM32 automatically.

1. Clone the repository

```console
$ git clone --recurse-submodules https://github.com/eyeonspringfield/thesis-monorepo
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

3. Compile wasm2wat
```console
$ cd toolchain/wabt
$ mkdir build && cd build
$ cmake .. -DBUILD_TESTS=OFF -DBUILD_TOOLS=ON -DCMAKE_BUILD_TYPE=Release
$ make wasm2wat
```

4. Compile Walrus for ARM32

```console
$ cd walrus
$ cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -H. -Bout/release/arm -DWALRUS_ARCH=arm -DWALRUS_HOST=linux -DWALRUS_MODE=release -DWALRUS_OUTPUT=shell -DCMAKE_C_COMPILER=arm-linux-gnueabi-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabi-g++ -DCMAKE_EXE_LINKER_FLAGS="-static" -GNinja
$ ninja -Cout/release/arm
```

5. Compile the C and C++ programs in the `src` folder to WASM & WAT

```console
$ cd ..
$ make
```

This will compile all C and C++ files in the `src` folder to WASM files in the `build` folder using Emscripten, and then convert them to WAT files using `wasm2wat`.

Or compile individual files manually:

```console
$ source toolchain/emsdk/emsdk_env.sh && toolchain/emsdk/upstream/emscripten/emcc src/main.c -O0 -s STANDALONE_WASM -s WASM_BIGINT=0 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -o build/main.wasm
$ toolchain/wabt/build/wasm2wat build/wasm/main.wasm -o build/wat/main.wat
```

6. Run the compiled WASM programs using Walrus and QEMU

```console
$ make run
```

Or run individual files manually:

```console
$ mkdir -p logs
$ qemu-arm -d in_asm -D logs/main.log ./walrus/out/release/arm/walrus --jit build/main.wasm
```

The log files in the `logs` folder will contain the instructions executed by Walrus for each program.

To print an analysis of the logs, run the following script:

```console
$ python3 scripts/analyze_logs.py
```

Additional make commands:
- `make clean` => `rm -rf build`
- `make clean-logs` => `rm -rf logs`

### Required tools
- CMake
- GNU Make
- Ninja
- Python
- QEMU
- gcc-arm-linux-gnueabi & g++-arm-linux-gnueabi
- gcc-arm-linux-gnueabihf & g++-arm-linux-gnueabihf

To install the required tools on Debian, run:

```console
# apt install cmake make ninja-build python3 qemu-user gcc-arm-linux-gnueabi g++-arm-linux-gnueabi gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
```
### Additional notes
Walrus has been modified to compile under QEMU ARM32. The modifications are in the `thesis-mods` branch.

SLJIT has been modified to emit unique, unused `MOVW`+`MOVT` instruction pairs when emitting JITed code. This is to make analysis easier.

When emitting a function prologue, SLJIT emits the following instructions:
```asm
e30cc123  movw     ip, #0xc123
e34cc456  movt     ip, #0xc456
```

When emitting a function epilogue, SLJIT emits the following instructions:
```asm
e30ccabc  movw     ip, #0xcabc
e34ccdef  movt     ip, #0xcdef
```

Logs can be grepped for these instructions to find the start and end of JITed functions.