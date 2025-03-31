#include "ds/tests/test_string.h"

/**
 * @brief BasecTest the creation of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_create(c_str fail_message) {
    BasecString* string = NULL;

    basec_string_create(&string, "Hello, World!", 16);

    if (strncmp(string->data, "Hello, World!", 13) != 0) {
        (void)strncpy(
            fail_message,
            "String data does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (string->length != 13) {
        (void)strncpy(
            fail_message,
            "String length does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (string->capacity != 16) {
        (void)strncpy(
            fail_message,
            "String capacity does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    basec_string_destroy(&string);

    return true;
}

/**
 * @brief BasecTest the destruction of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_destroy(c_str fail_message) {
    BasecString* string = NULL;

    basec_string_create(&string, "Hello, World!", 13);
    basec_string_destroy(&string);

    if (string != NULL) {
        (void)strncpy(
            fail_message,
            "String was not destroyed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    return true;
}

/**
 * @brief Add String tests to a test suite
 * @param test_suite The test suite to add the tests to
 * @return The result of the operation
 */
BasecTestResult test_string_add_tests(BasecTestSuite* test_suite) {
    BasecTestResult  test_result = BASEC_TEST_SUCCESS;
    BasecTest*       create_test = NULL;
    BasecTest*       destroy_test = NULL;
    BasecTestModule* test_module = NULL;

    test_result = basec_test_create(
        &create_test,
        "test_string_create",
        "Test the creation of a string",
        &test_string_create
    );
    if (test_result != BASEC_TEST_SUCCESS) return test_result;

    test_result = basec_test_create(
        &destroy_test,
        "test_string_destroy",
        "Test the destruction of a string",
        &test_string_destroy
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        return test_result;
    }
    
    test_result = basec_test_module_create(
        &test_module,
        "String"
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&destroy_test);
        return test_result;
    }

    test_result = basec_test_module_add_test(test_module, create_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&test_module);
        return test_result;
    }

    test_result = basec_test_module_add_test(test_module, destroy_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&test_module);
        return test_result;
    }
    
    test_result = basec_test_suite_add_module(test_suite, test_module);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_module_destroy(&test_module);
        return test_result;
    }

    return BASEC_TEST_SUCCESS;
}