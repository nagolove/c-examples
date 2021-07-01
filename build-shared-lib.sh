#!/usr/bin/env bash

EXECUTABLE="a.out"
gcc main.cpp -o $EXECUTABLE -O2 -fPIC -faggressive-loop-optimizations -Wall -g -std=c++17
strip $EXECUTABLE
