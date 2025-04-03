#ifndef BASEC_ARRAY_TEST_H
#define BASEC_ARRAY_TEST_H

#include "util/basec_test.h"
#include "ds/basec_array.h"

/**
 * @brief Test the creation of an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_create(c_str fail_message);

/**
 * @brief Test appending an element to an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_append(c_str fail_message);

/**
 * @brief Test pushing an element to an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_push(c_str fail_message);

/**
 * @brief Test popping an element from an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_pop(c_str fail_message);

/**
 * @brief Test getting an element from an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_get(c_str fail_message);

/**
 * @brief Test setting an element in an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_set(c_str fail_message);

/**
 * @brief Test checking if an array contains an element
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_contains(c_str fail_message);

/**
 * @brief Test finding an element in an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_find(c_str fail_message);

/**
 * @brief Test finding all instances of an element in an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_find_all(c_str fail_message);

/**
 * @brief Test the destruction of an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_destroy(c_str fail_message);

/**
 * @brief Add Array tests to a test suite
 * @param test_suite The test suite to add the tests to
 * @return The result of the operation
 */
BasecTestResult test_array_add_tests(BasecTestSuite* test_suite);

#endif