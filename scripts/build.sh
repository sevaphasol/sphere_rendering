#!/bin/bash

mkdir -p build

pushd build
cmake ..
make -j$(nproc)
make install
popd

ln -sf build/compile_commands.json
