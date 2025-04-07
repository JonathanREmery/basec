#include <stdio.h>

#include "util/basec_build.h"
#include "ds/basec_string.h"
#include "ds/basec_array.h"

static void _build(void) {
    BuildSystem* build_system = NULL;
    BuildTarget  basec        = {
        .name     = "basec",
        .bin      = "bin/basec",
        .sources  = {
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

    c_str        str     = "A1, B2, C3, D4";
    BasecString* string  = NULL;
    BasecArray*  indices = NULL;
    BasecArray*  values  = NULL; 

    basec_string_handle_result(
        basec_string_create(&string, str, strlen(str))
    );

    (void)printf("[Debug][String] string: %s\n", string->data);

    (void)printf("[Debug][String] append(\", E5\")\n");
    basec_string_handle_result(
        basec_string_append(
            string,
            ", E5"
        )
    );
    (void)printf("[Debug][String] -> %s\n", string->data);

    (void)printf("[Debug][String] replace(\", \", \"|\")\n");
    basec_string_handle_result(
        basec_string_replace(
            string,
            ", ",
            "|",
            &string
        )
    );
    (void)printf("[Debug][String] -> %s\n", string->data);

    basec_string_handle_result(
        basec_string_split(
            string,
            "|",
            &values
        )
    );

    basec_string_handle_result(
        basec_string_find_all(
            string,
            "|",
            &indices
        )
    );

    (void)printf("[Debug][String] find_all(\"|\")\n");
    for (u64 i = 0; i < indices->length; i++) {
        u64 index;
        basec_array_handle_result(basec_array_get(indices, i, &index));
        (void)printf("[Debug][String] -> %lu\n", index);
    }
    if (indices->length == 0) (void)printf("[Debug][String] -> none\n");

    (void)printf("[Debug][String] split(\"|\")\n");
    for (u64 i = 0; i < values->length; i++) {
        BasecString* value;
        basec_array_handle_result(basec_array_get(values, i, &value));
        (void)printf("[Debug][String] -> %s\n", value->data);
    }
    if (values->length == 0) (void)printf("[Debug][String] -> none\n");

    basec_string_handle_result(
        basec_string_destroy(
            &string
        )
    );

    basec_array_handle_result(
        basec_array_destroy(
            &indices
        )
    );

    basec_string_handle_result(
        basec_strings_destroy(
            &values
        )
    );

    return 0;
}
