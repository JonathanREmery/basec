#include <stdio.h>
#include <stdlib.h>

#include "ds/basec_string.h"

int main(void) {
    BasecString* string = basec_string_create(", ", 128);
    printf("string: %s\n", basec_string_c_str(string));
    printf("-> length: %zu\n", string->length);
    printf("-> capacity: %zu\n\n", string->capacity);
    
    basec_string_prepend(string, "Hello");
    printf("string: %s\n", basec_string_c_str(string));
    printf("-> length: %zu\n", string->length);
    printf("-> capacity: %zu\n\n", string->capacity);

    basec_string_append(string, "World!");
    printf("string: %s\n", basec_string_c_str(string));
    printf("-> length: %zu\n", string->length);
    printf("-> capacity: %zu\n", string->capacity);

    basec_string_destroy(string);
    return 0;
}