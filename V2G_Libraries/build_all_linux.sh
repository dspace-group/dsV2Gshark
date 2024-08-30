#!/bin/bash

# build default lib
export IFLAGS_LUA=-I"../Third_Party/lua/lua-52/include" # 53 and 54 are compatible with 52
export BINARY_OUT_NAME=v2gLib.so
make -C v2gLib -f makefile_linux all
if [ $? -ne 0 ]; then
    echo "failed to build v2gLib!"
    exit 1
fi

# build lua 5.1 lib
export IFLAGS_LUA=-I"../Third_Party/lua/lua-51/include"
export BINARY_OUT_NAME=v2gLib_51.so
make -C v2gLib -f makefile_linux clean-obj all
if [ $? -ne 0 ]; then
    echo "failed to build v2gLib for Lua51!"
    exit 1
fi

echo "Lua libs built successfully!"