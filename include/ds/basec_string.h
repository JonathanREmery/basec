#ifndef BASEC_STRING_H
#define BASEC_STRING_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char*  data;
    size_t length;
    size_t capacity;
} BasecString;

BasecString* basec_string_create(const char* str, size_t capacity);
void basec_string_destroy(BasecString* str);

#endif
