#include <stdio.h>
#include <stdlib.h>

#include "ds/basec_string.h"

int main(void) {
    BasecString* string = NULL;

    c_str str;
    u64 length;
    u64 capacity;

    basec_string_handle_result(basec_string_create(&string, ", ", 128));

    basec_string_handle_result(basec_string_c_str(&string, &str));
    basec_string_handle_result(basec_string_length(&string, &length));
    basec_string_handle_result(basec_string_capacity(&string, &capacity));

    printf("string: %s\n", str);
    printf("-> length: %zu\n", length);
    printf("-> capacity: %zu\n\n", capacity);

    basec_string_handle_result(basec_string_prepend(&string, "Hello"));

    basec_string_handle_result(basec_string_c_str(&string, &str));
    basec_string_handle_result(basec_string_length(&string, &length));
    basec_string_handle_result(basec_string_capacity(&string, &capacity));

    printf("string: %s\n", str);
    printf("string: %s\n", str);
    printf("-> length: %zu\n", length);
    printf("-> capacity: %zu\n\n", capacity);

    basec_string_handle_result(basec_string_append(&string, "World!"));

    basec_string_handle_result(basec_string_c_str(&string, &str));
    basec_string_handle_result(basec_string_length(&string, &length));
    basec_string_handle_result(basec_string_capacity(&string, &capacity));

    printf("string: %s\n", str);
    printf("-> length: %zu\n", length);
    printf("-> capacity: %zu\n", capacity);

    basec_string_handle_result(basec_string_destroy(&string));

    return 0;
}