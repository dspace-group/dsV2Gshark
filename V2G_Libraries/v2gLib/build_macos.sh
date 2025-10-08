#!/bin/bash

# build default lib
export IFLAGS_LUA=-I"../Third_Party/lua/lua-52/include" # 53 and 54 are compatible with 52
export BINARY_OUT_NAME=v2gLib.so
make -f makefile_macos all
if [ $? -ne 0 ]; then
    echo "failed to build v2gLib!"
    exit 1
fi

echo "Lua libs built successfully!"
