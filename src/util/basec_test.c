#include "util/basec_test.h"

/**
 * @brief Handle a test result
 * @param result The result to handle
 */
void basec_test_handle_result(BasecTestResult result) {
    switch (result) {
        case BASEC_TEST_SUCCESS:
            break;
        case BASEC_TEST_NULL_POINTER:
            (void)printf("[Error][Test] Null pointer passed to function\n");
            break;
        case BASEC_TEST_ALLOCATION_FAILURE:
            (void)printf("[Error][Test] Failed to allocate memory\n");
            break;
        case BASEC_TEST_ARRAY_FAILURE:
            (void)printf("[Error][Test] An array operation failed\n");
            break;
        case BASEC_TEST_RUN_FAILURE:
            (void)printf("[Error][Test] Failed to run test\n");
            break;
        default:
            (void)printf("[Error][Test] Unknown error\n");
            break;
    }
}

/**
 * @brief Create a test
 * @param test The test to create
 * @param name The name of the test
 * @param description The description of the test
 * @param test_fn The function to run the test
 * @return The result of the operation
 */
BasecTestResult basec_test_create(
    BasecTest** test,
    c_str  name,
    c_str  description,
    bool   (*test_fn)(c_str fail_message)
) {
    if (test == NULL || name == NULL || description == NULL || test_fn == NULL) {
        return BASEC_TEST_NULL_POINTER;
    }

    *test = (BasecTest*)malloc(sizeof(BasecTest));
    if (*test == NULL) return BASEC_TEST_ALLOCATION_FAILURE;

    (*test)->name         = name;
    (*test)->description  = description;
    (*test)->test_fn      = test_fn;
    (*test)->is_success   = false;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Run a test
 * @param test The test to run
 * @return The result of the operation
 */
BasecTestResult basec_test_run(BasecTest* test) {
    if (test == NULL || test->test_fn == NULL) return BASEC_TEST_NULL_POINTER;

    test->is_success = test->test_fn(test->fail_message);
    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Destroy a test
 * @param test The test to destroy
 * @return The result of the operation
 */
BasecTestResult basec_test_destroy(BasecTest** test) {
    if (*test == NULL) return BASEC_TEST_NULL_POINTER;

    free(*test);
    *test = NULL;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Create a test module
 * @param test_module The test module to create
 * @param name The name of the test module
 * @return The result of the operation
 */
BasecTestResult basec_test_module_create(
    BasecTestModule** test_module,
    c_str name
) {
    if (test_module == NULL || name == NULL) {
        return BASEC_TEST_NULL_POINTER;
    }
    
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;

    *test_module = (BasecTestModule*)malloc(sizeof(BasecTestModule));
    if (*test_module == NULL) return BASEC_TEST_ALLOCATION_FAILURE;

    (*test_module)->name  = name;
    (*test_module)->tests = NULL;

    array_result = basec_array_create(
        &(*test_module)->tests,
        sizeof(BasecTest*),
        10
    );
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Add a test to a test module
 * @param test_module The test module to add the test to
 * @param test The test to add
 * @return The result of the operation
 */
BasecTestResult basec_test_module_add_test(BasecTestModule* test_module, BasecTest* test) {
    if (test_module == NULL || test == NULL) return BASEC_TEST_NULL_POINTER;

    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;

    array_result = basec_array_append(test_module->tests, &test);
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Run a test module
 * @param test_module The test module to run
 * @param passed_tests The array to store passed tests
 * @param failed_tests The array to store failed tests
 * @return The result of the operation
 */
BasecTestResult basec_test_module_run(
    BasecTestModule* test_module,
    BasecArray* passed_tests,
    BasecArray* failed_tests
) {
    if (test_module == NULL) return BASEC_TEST_NULL_POINTER;

    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecTest*       test         = NULL;
    BasecTestResult  test_result  = BASEC_TEST_SUCCESS;

    for (u64 i = 0; i < test_module->tests->length; i++) {
        array_result = basec_array_get(test_module->tests, i, &test);
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

        test_result = basec_test_run(test);
        if (test_result != BASEC_TEST_SUCCESS) return test_result;

        if (test->is_success) {
            array_result = basec_array_append(passed_tests, &test);
            if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;
        } else {
            array_result = basec_array_append(failed_tests, &test);
            if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;
        }
    }

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Destroy a test module
 * @param test_module The test module to destroy
 */
BasecTestResult basec_test_module_destroy(BasecTestModule** test_module) {
    if (test_module == NULL) return BASEC_TEST_NULL_POINTER;

    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecTest*       test         = NULL;
    BasecTestResult  test_result  = BASEC_TEST_SUCCESS;

    for (u64 i = 0; i < (*test_module)->tests->length; i++) {
        array_result = basec_array_get((*test_module)->tests, i, &test);
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

        test_result = basec_test_destroy(&test);
        if (test_result != BASEC_TEST_SUCCESS) return test_result;
    }

    array_result = basec_array_destroy(&(*test_module)->tests);
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

    free(*test_module);
    *test_module = NULL;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Create a test suite
 * @param test_suite The test suite to create
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_create(BasecTestSuite** test_suite) {
    if (test_suite == NULL) return BASEC_TEST_NULL_POINTER;

    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;

    *test_suite = (BasecTestSuite*)malloc(sizeof(BasecTestSuite));
    if (*test_suite == NULL) return BASEC_TEST_ALLOCATION_FAILURE;

    (*test_suite)->modules = NULL;
    (*test_suite)->passed_tests = NULL;
    (*test_suite)->failed_tests = NULL;

    array_result = basec_array_create(
        &(*test_suite)->modules,
        sizeof(BasecTestModule*),
        5
    );
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;
    
    array_result = basec_array_create(
        &(*test_suite)->passed_tests,
        sizeof(BasecTest*),
        10
    );
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;
    
    array_result = basec_array_create(
        &(*test_suite)->failed_tests,
        sizeof(BasecTest*),
        10
    );
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Add a test module to a test suite
 * @param test_suite The test suite to add the test module to
 * @param test_module The test module to add
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_add_module(
    BasecTestSuite*  test_suite,
    BasecTestModule* test_module
) {
    if (test_suite == NULL || test_module == NULL) return BASEC_TEST_NULL_POINTER;

    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;

    array_result = basec_array_append(test_suite->modules, &test_module);
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Run a test suite
 * @param test_suite The test suite to run
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_run(BasecTestSuite* test_suite) {
    if (test_suite == NULL) return BASEC_TEST_NULL_POINTER;

    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecTestModule* test_module  = NULL;
    BasecTestResult  test_result  = BASEC_TEST_SUCCESS;

    for (u64 i = 0; i < test_suite->modules->length; i++) {
        array_result = basec_array_get(test_suite->modules, i, &test_module);
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

        test_result = basec_test_module_run(
            test_module,
            test_suite->passed_tests,
            test_suite->failed_tests
        );
        if (test_result != BASEC_TEST_SUCCESS) return test_result;
    }

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Destroy a test suite
 * @param test_suite The test suite to destroy
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_destroy(BasecTestSuite** test_suite) {
    if (test_suite == NULL) return BASEC_TEST_NULL_POINTER;

    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecTestResult  test_result  = BASEC_TEST_SUCCESS;
    BasecTestModule* test_module  = NULL;

    for (u64 i = 0; i < (*test_suite)->modules->length; i++) {
        array_result = basec_array_get((*test_suite)->modules, i, &test_module);
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

        test_result = basec_test_module_destroy(&test_module);
        if (test_result != BASEC_TEST_SUCCESS) return test_result;
    }

    array_result = basec_array_destroy(&(*test_suite)->modules);
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;
    
    array_result = basec_array_destroy(&(*test_suite)->passed_tests);
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

    array_result = basec_array_destroy(&(*test_suite)->failed_tests);
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

    free(*test_suite);
    *test_suite = NULL;

    return BASEC_TEST_SUCCESS;
}

/**
 * @brief Print the results of a test suite
 * @param test_suite The test suite to print the results of
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_print_results(BasecTestSuite* test_suite) {
    if (test_suite == NULL) return BASEC_TEST_NULL_POINTER;
    
    const char* GREEN = "\033[0;32m";
    const char* RED = "\033[0;31m";
    const char* YELLOW = "\033[0;33m";
    const char* BLUE = "\033[0;34m";
    const char* BOLD = "\033[1m";
    const char* RESET = "\033[0m";
    
    const char* HORIZONTAL = "─";
    const char* VERTICAL = "│";
    const char* TEE = "├";
    const char* CORNER = "└";
    const char* ARROW = "→";
    
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecTestModule* test_module  = NULL;
    BasecTest*       test         = NULL;
    u64 successful_tests          = test_suite->passed_tests->length;
    u64 failed_tests              = test_suite->failed_tests->length;
    u64 total_tests               = successful_tests + failed_tests;
    
    (void)printf("\n%s%s===================================%s\n", BOLD, BLUE, RESET);
    (void)printf("%s%s         BASEC TEST RESULTS        %s\n", BOLD, BLUE, RESET);
    (void)printf("%s%s===================================%s\n\n", BOLD, BLUE, RESET);

    for (u64 i = 0; i < test_suite->modules->length; i++) {
        array_result = basec_array_get(test_suite->modules, i, &test_module);
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

        (void)printf("%s%s[MODULE] %s%s\n", BOLD, YELLOW, test_module->name, RESET);
        
        for (u64 j = 0; j < test_module->tests->length; j++) {
            array_result = basec_array_get(test_module->tests, j, &test);
            if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;

            if (j < test_module->tests->length - 1) {
                (void)printf("  %s%s%s%s ", BOLD, TEE, HORIZONTAL, RESET);
            } else {
                (void)printf("  %s%s%s%s ", BOLD, CORNER, HORIZONTAL, RESET);
            }

            if (test->is_success) {
                (void)printf("%s%s✓%s %s\n", GREEN, BOLD, RESET, test->name);
            } else {
                (void)printf("%s%s✗%s %s\n", RED, BOLD, RESET, test->name);
                
                if (j < test_module->tests->length - 1) {
                    (void)printf(
                        "  %s  %s%s %s%s\n",
                        VERTICAL,
                        RED,
                        ARROW,
                        test->fail_message,
                        RESET
                    );
                } else {
                    (void)printf("    %s%s %s%s\n", RED, ARROW, test->fail_message, RESET);
                }
            }
        }
        
        if (i < test_suite->modules->length - 1) {
            (void)printf("\n");
        }
    }
    
    (void)printf("\n%s%s===================================%s\n", BOLD, BLUE, RESET);
    
    float pass_percentage = (total_tests > 0) ? 
                            ((float)successful_tests / total_tests) * 100.0f :
                            0.0f;
    (void)printf("  %sTotal tests:%s %lu\n", BOLD, RESET, total_tests);
    
    if (failed_tests == 0) {
        (void)printf(
            "  %s%sPassed:%s %lu/%lu (100%%)\n",
            BOLD,
            GREEN,
            RESET,
            successful_tests,
            total_tests
        );
    } else {
        (void)printf(
            "  %s%sPassed:%s %lu/%lu (%.1f%%)\n",
            BOLD,
            (pass_percentage >= 80.0f) ? GREEN : (pass_percentage >= 50.0f) ? YELLOW : RED,
            RESET,
            successful_tests,
            total_tests,
            pass_percentage
        );

        (void)printf(
            "  %s%sFailed:%s %lu/%lu\n",
            BOLD,
            RED,
            RESET,
            failed_tests,
            total_tests
        );
        
        (void)printf("\n%s%s FAILURE DETAILS %s\n", BOLD, RED, RESET);
        (void)printf("%s%s-------------------%s\n", BOLD, RED, RESET);
        
        for (u64 i = 0; i < failed_tests; i++) {
            array_result = basec_array_get(test_suite->failed_tests, i, &test);
            if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_TEST_ARRAY_FAILURE;
            
            (void)printf("%s%s%lu)%s %s\n", BOLD, RED, i + 1, RESET, test->name);
            (void)printf("   %s%s%s %s%s\n\n", BOLD, RED, ARROW, test->fail_message, RESET);
        }
    }
    
    (void)printf("%s%s===================================%s\n\n", BOLD, BLUE, RESET);

    return BASEC_TEST_SUCCESS;
}
