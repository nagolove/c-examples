#!/usr/bin/env bash

EXECUTABLE="hello-world"
#gcc main.cpp -o $EXECUTABLE -O2 -fPIC -faggressive-loop-optimizations -Wall -g -std=c++17
#gcc main-hello-world.cpp -o $EXECUTABLE -O0 -fPIC -Wall -g -std=c++17
#gcc main-hello-world.cpp -o $EXECUTABLE -O0 -Wall -g -std=c++17
#gcc main-hello-world.cpp -o $EXECUTABLE -O0 -g3 -gdwarf -Wall -g -std=c++17
#gcc main-hello-world.cpp -o $EXECUTABLE -O0 -g3 -ggdb -gdwarf -Wall -g -std=c++17
#gcc main-hello-world.cpp -o $EXECUTABLE -ggdb -Wall -g -std=c++17
gcc main-hello-world.cpp -o $EXECUTABLE -ggdb -Wall -std=c++17
strip $EXECUTABLE
