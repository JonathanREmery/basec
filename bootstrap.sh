#!/bin/bash
gcc -Wall -Wextra -pedantic -o bin/basec src/main.c src/util/basec_build.c src/ds/basec_string.c -Iinclude
