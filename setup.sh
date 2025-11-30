#!/usr/bin/bash
set -e

# Run this script from the root directory of the repository to automatically set up the development environment.

cd walrus || { echo "Walrus directory not found. Are you running script from repository root dir?" && exit 1; }
git checkout thesis-mods

cd ../toolchain/emsdk || exit 1
./emsdk install latest
./emsdk activate latest

cd ../wabt || exit 1
mkdir build && cd build || exit 1
cmake .. -DBUILD_TESTS=OFF -DBUILD_TOOLS=ON -DCMAKE_BUILD_TYPE=Release
make wasm2wat

cd ../../walrus || exit 1
cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -H. -Bout/release/arm -DWALRUS_ARCH=arm -DWALRUS_HOST=linux -DWALRUS_MODE=release -DWALRUS_OUTPUT=shell -DCMAKE_C_COMPILER=arm-linux-gnueabi-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabi-g++ -DCMAKE_EXE_LINKER_FLAGS="-static" -GNinja
ninja -Cout/release/arm
cd .. || exit 1

echo
echo "Setup complete. To compile programs in src, use:"
echo "make"
echo
echo "To run compiled programs with walrus, use:"
echo "make run"