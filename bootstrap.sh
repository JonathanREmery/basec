#!/bin/bash
mkdir -p bin
gcc -Wall -Wextra -pedantic -o bin/basec src/main.c src/util/basec_build.c src/ds/basec_string.c src/ds/basec_array.c -Iinclude
gcc -Wall -Wextra -pedantic -o bin/test src/test.c src/util/basec_build.c src/ds/basec_string.c src/ds/basec_array.c src/util/basec_test.c src/ds/tests/test_string.c -Iinclude