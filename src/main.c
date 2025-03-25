#include <stdio.h>
#include <stdlib.h>

#include "util/basec_build.h"
#include "ds/basec_string.h"

static void _build(void) {
    BuildSystem* build_system = NULL;
    basec_build_handle_result(basec_build_system_create(&build_system));

    BuildTarget basec = {
        .name = "basec",
        .sources = {
            "src/main.c",
            "src/util/basec_build.c",
            "src/ds/basec_string.c",
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