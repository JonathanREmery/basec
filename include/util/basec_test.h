/**
 * @file basec_test.h
 * @brief A testing framework
 */
#ifndef BASEC_TEST_H
#define BASEC_TEST_H

#include "basec_types.h"
#include "ds/basec_array.h"

#define BASEC_TEST_FAIL_MESSAGE_MAX_LEN 128

/**
 * @struct BasecTest
 * @brief A test
 */
typedef struct {
    c_str name;
    c_str description;
    bool  (*test_fn)(c_str fail_message);
    bool  is_success;
    c8    fail_message[BASEC_TEST_FAIL_MESSAGE_MAX_LEN];
} BasecTest;

typedef struct {
    c_str       name;
    BasecArray* tests;
} BasecTestModule;

/**
 * @struct BasecTestSuite
 * @brief A test suite
 */
typedef struct {
    BasecArray* modules;
} BasecTestSuite;

/**
 * @enum BasecTestResult
 * @brief The result of a test operation
 */
typedef enum {
    BASEC_TEST_SUCCESS,
    BASEC_TEST_NULL_POINTER,
    BASEC_TEST_ALLOCATION_FAILURE,
    BASEC_TEST_ARRAY_FAILURE,
    BASEC_TEST_RUN_FAILURE,
} BasecTestResult;

/**
 * @brief Handle a test result
 * @param result The result to handle
 */
void basec_test_handle_result(BasecTestResult result);

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
);

/**
 * @brief Run a test
 * @param test The test to run
 * @return The result of the operation
 */
BasecTestResult basec_test_run(BasecTest* test);

/**
 * @brief Destroy a test
 * @param test The test to destroy
 * @return The result of the operation
 */
BasecTestResult basec_test_destroy(BasecTest** test);

/**
 * @brief Create a test module
 * @param test_module The test module to create
 * @param name The name of the test module
 * @return The result of the operation
 */
BasecTestResult basec_test_module_create(
    BasecTestModule** test_module,
    c_str name
);

/**
 * @brief Add a test to a test module
 * @param test_module The test module to add the test to
 * @param test The test to add
 * @return The result of the operation
 */
BasecTestResult basec_test_module_add_test(BasecTestModule* test_module, BasecTest* test);

/**
 * @brief Run a test module
 * @param test_module The test module to run
 * @return The result of the operation
 */
BasecTestResult basec_test_module_run(BasecTestModule* test_module);

/**
 * @brief Destroy a test module
 * @param test_module The test module to destroy
 * @return The result of the operation
 */
BasecTestResult basec_test_module_destroy(BasecTestModule** test_module);

/**
 * @brief Create a test suite
 * @param test_suite The test suite to create
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_create(BasecTestSuite** test_suite);

/**
 * @brief Add a test module to a test suite
 * @param test_suite The test suite to add the test module to
 * @param test_module The test module to add
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_add_module(
    BasecTestSuite*  test_suite,
    BasecTestModule* test_module
);

/**
 * @brief Run a test suite
 * @param test_suite The test suite to run
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_run(BasecTestSuite* test_suite);

/**
 * @brief Destroy a test suite
 * @param test_suite The test suite to destroy
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_destroy(BasecTestSuite** test_suite);

/**
 * @brief Print the results of a test suite
 * @param test_suite The test suite to print the results of
 * @return The result of the operation
 */
BasecTestResult basec_test_suite_print_results(BasecTestSuite* test_suite);

#endif