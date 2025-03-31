#include "util/basec_build.h"
#include "ds/tests/test_string.h"

static void _build(void) {
    BuildSystem* build_system = NULL;
    BuildTarget  test         = {
        .name = "test",
        .sources = {
            "src/test.c",
            "src/util/basec_build.c",
            "src/ds/basec_string.c",
            "src/ds/basec_array.c",
            "src/util/basec_test.c",
            "src/ds/tests/test_string.c",
        },
        .includes = {
            "include",
        }
    };

    basec_build_handle_result(basec_build_system_create(&build_system));
    basec_build_handle_result(basec_build_system_add_target(build_system, test));
    basec_build_handle_result(basec_build_system_build(build_system));
    basec_build_handle_result(basec_build_system_destroy(&build_system));
}

int main(void) {
    _build();

    BasecTestSuite* test_suite = NULL;

    basec_test_handle_result(basec_test_suite_create(&test_suite));

    basec_test_handle_result(test_string_add_tests(test_suite));

    basec_test_handle_result(basec_test_suite_run(test_suite));
    basec_test_handle_result(basec_test_suite_print_results(test_suite));

    basec_test_handle_result(basec_test_suite_destroy(&test_suite));

    return 0;
}