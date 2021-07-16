#!/usr/bin/env bash

echo "input00.txt"
cat ./bin/varsizearray_testdata/input00.txt | xargs ./bin/variable-sized-array

echo "input02.txt"
cat ./bin/varsizearray_testdata/input02.txt.txt | xargs ./bin/variable-sized-array

echo "input04.txt"
cat ./bin/varsizearray_testdata/input04.txt.txt | xargs ./bin/variable-sized-array

echo "input07.txt"
cat ./bin/varsizearray_testdata/input07.txt | xargs ./bin/variable-sized-array
