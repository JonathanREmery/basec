#ifndef BASEC_STRING_TEST_H
#define BASEC_STRING_TEST_H

#include "util/basec_test.h"
#include "ds/basec_string.h"

/**
 * @brief BasecTest the creation of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_create(c_str fail_message);

/**
 * @brief BasecTest the destruction of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_destroy(c_str fail_message);

/**
 * @brief Add String tests to a test suite
 * @param test_suite The test suite to add the tests to
 * @return The result of the operation
 */
BasecTestResult test_string_add_tests(BasecTestSuite* test_suite);

#endif