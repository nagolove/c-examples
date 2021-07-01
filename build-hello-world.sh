#!/usr/bin/env bash

EXECUTABLE="hello-world"
gcc main.cpp -o $EXECUTABLE -O2 -fPIC -faggressive-loop-optimizations -Wall -g -std=c++17
strip $EXECUTABLE
