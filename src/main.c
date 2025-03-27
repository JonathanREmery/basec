#include <stdio.h>
#include <stdlib.h>

#include "util/basec_build.h"
#include "ds/basec_string.h"
#include "ds/basec_array.h"

static void _build(void) {
    BuildSystem* build_system = NULL;
    BuildTarget  basec        = {
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

    basec_build_handle_result(basec_build_system_create(&build_system));

    basec_build_handle_result(basec_build_system_add_target(build_system, basec));
    basec_build_handle_result(basec_build_system_build(build_system));

    basec_build_handle_result(basec_build_system_destroy(&build_system));
}

int main(void) {
    _build();

    c_str        str    = "A1, B2, C3, D4";
    BasecString* string = NULL;
    // BasecArray*  values = NULL; 

    (void)printf("[Debug][String] str: %s\n", str);

    basec_string_handle_result(
        basec_string_create(
            &string,
            str,
            32
        )
    );

    basec_string_handle_result(
        basec_string_replace(
            string,
            ", ",
            "|",
            &string
        )
    );

    (void)printf("[Debug][String] replace(\"A\", \"B\")\n");
    (void)printf("[Debug][String] -> %s\n", string->data);

    // basec_string_handle_result(
    //     basec_string_split(
    //         string,
    //         ", ",
    //         &values
    //     )
    // );

    // (void)printf("[Debug][String] split(\", \")\n");
    // for (u64 i = 0; i < values->length; i++) {
    //     BasecString* value;
    //     basec_array_handle_result(basec_array_get(values, i, &value));
    //     (void)printf("[Debug][String] -> %s\n", value->data);
    // }
    // if (values->length == 0) (void)printf("[Debug][String] -> none\n");

    basec_string_handle_result(
        basec_string_destroy(
            &string
        )
    );

    // basec_string_handle_result(
    //     basec_strings_destroy(
    //         &values
    //     )
    // );

    BasecArray* arr;
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
        u8 element;
        basec_array_handle_result(basec_array_get(arr, i, &element));
        (void)printf("-> [%zu] %d\n", i, element);

        u8 incremented_element = element + 1;
        basec_array_handle_result(basec_array_set(arr, i, &incremented_element));
    }

    x = 3;
    bool contains;
    basec_array_handle_result(basec_array_contains(arr, &x, &contains));
    (void)printf("contains %d: %d\n", x, contains);

    u64 index;
    basec_array_handle_result(basec_array_find(arr, &x, &index));
    (void)printf("index of %d: %zu\n", x, index);

    (void)printf("popping from array\n");

    u8 y;
    while (basec_array_pop(arr, &y) == BASEC_ARRAY_SUCCESS) {
        (void)printf("-> [%zu] %d\n", arr->length, y);
    }

    basec_array_handle_result(basec_array_destroy(&arr));

    return 0;
}
