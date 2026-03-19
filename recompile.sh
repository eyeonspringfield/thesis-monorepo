#!/usr/bin/bash
set -e

# Recompile Walrus with the latest changes.

cd walrus || { echo "Walrus directory not found. Are you running script from repository root dir?" && exit 1; }

rm -rf out/

cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -H. -Bout/release/arm -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON -DWALRUS_ARCH=arm -DWALRUS_HOST=linux -DWALRUS_MODE=release -DWALRUS_OUTPUT=shell -DCMAKE_C_COMPILER=arm-linux-gnueabi-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabi-g++ -DCMAKE_EXE_LINKER_FLAGS="-static" -DCMAKE_COLOR_DIAGNOSTICS=ON -GNinja
ninja -Cout/release/arm

cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -H. -Bout/release/arm-emu -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON -DWALRUS_ARCH=arm -DWALRUS_HOST=linux -DWALRUS_MODE=release -DWALRUS_OUTPUT=shell -DCMAKE_C_COMPILER=arm-linux-gnueabi-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabi-g++ -DCMAKE_EXE_LINKER_FLAGS="-static" -DWALRUS_CUSTOM_INSTRUCTIONS=ON -DCMAKE_COLOR_DIAGNOSTICS=ON -GNinja
ninja -Cout/release/arm-emu

echo
echo "Compiled"