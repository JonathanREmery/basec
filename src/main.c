#include <stdio.h>
#include <stdlib.h>

#include "util/basec_build.h"
#include "ds/basec_string.h"
#include "ds/basec_array.h"

static void _build(void) {
    BuildSystem* build_system = NULL;
    basec_build_handle_result(basec_build_system_create(&build_system));

    BuildTarget basec = {
        .name = "basec",
        .sources = {
            "src/main.c",
            "src/util/basec_build.c",
            "src/ds/basec_string.c",
            "src/ds/basec_array.c",
        },
        .includes = {
            "include",
        }
    };

    basec_build_handle_result(basec_build_system_add_target(build_system, basec));
    basec_build_handle_result(basec_build_system_build(build_system));

    basec_build_handle_result(basec_build_system_destroy(&build_system));
}

int main(void) {
    _build();

    BasecString* string = NULL;

    c_str str;
    u64 length;
    u64 capacity;

    basec_string_handle_result(basec_string_create(&string, ", ", 128));

    basec_string_handle_result(basec_string_c_str(string, &str));
    basec_string_handle_result(basec_string_length(string, &length));
    basec_string_handle_result(basec_string_capacity(string, &capacity));

    (void)printf("string: %s\n", str);
    (void)printf("-> length: %zu\n", length);
    (void)printf("-> capacity: %zu\n\n", capacity);

    basec_string_handle_result(basec_string_prepend(string, "Hello"));

    basec_string_handle_result(basec_string_c_str(string, &str));
    basec_string_handle_result(basec_string_length(string, &length));
    basec_string_handle_result(basec_string_capacity(string, &capacity));

    (void)printf("string: %s\n", str);
    (void)printf("-> length: %zu\n", length);
    (void)printf("-> capacity: %zu\n\n", capacity);

    basec_string_handle_result(basec_string_append(string, "World!"));

    basec_string_handle_result(basec_string_c_str(string, &str));
    basec_string_handle_result(basec_string_length(string, &length));
    basec_string_handle_result(basec_string_capacity(string, &capacity));

    printf("string: %s\n", str);
    printf("-> length: %zu\n", length);
    printf("-> capacity: %zu\n\n", capacity);

    basec_string_handle_result(basec_string_destroy(&string));

    Array* arr;
    basec_array_handle_result(basec_array_create(&arr, sizeof(u8), 10));
    
    u8 x = 0;
    basec_array_handle_result(basec_array_push(arr, &x));
    x = 1;
    basec_array_handle_result(basec_array_push(arr, &x));
    x = 2;
    basec_array_handle_result(basec_array_push(arr, &x));
    x = 3;
    basec_array_handle_result(basec_array_push(arr, &x));

    (void)printf("array: 0x%lX\n", (u64)arr);
    for (u64 i = 0; i < arr->length; i++) {
        (void)printf("-> [%zu] %d\n", i, *((u8*)arr->data + i));
    }

    (void)printf("\npopping from array\n");

    u8 y;
    while (basec_array_pop(arr, &y) == BASEC_ARRAY_SUCCESS) {
        (void)printf("-> [%zu] %d\n", arr->length, y);
    }

    basec_array_handle_result(basec_array_destroy(&arr));

    return 0;
}
