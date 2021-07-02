#!/usr/bin/env bash

BIN_PATH="bin"
EXECUTABLE=$BIN_PATH"/shared-1.so"
echo "Executable: $EXECUTABLE"
gcc shared-lib.cpp -o $EXECUTABLE -O2 -fPIC -faggressive-loop-optimizations -Wall -g -std=c++17
strip $EXECUTABLE
