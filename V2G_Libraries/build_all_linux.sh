#!/bin/bash

make -C CertificateInfos -f makefile_linux dll
if [ $? -ne 0 ]; then
    echo "failed to build lua libs!"
    exit 1
fi

make -C V2GDecoder -f makefile_linux dll
if [ $? -ne 0 ]; then
    echo "failed to build lua libs!"
    exit 1
fi

echo "Lua libs built successfully!"