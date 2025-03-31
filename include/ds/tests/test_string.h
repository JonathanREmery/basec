#ifndef BASEC_STRING_TEST_H
#define BASEC_STRING_TEST_H

#include "util/basec_test.h"
#include "ds/basec_string.h"
#include "ds/basec_array.h"

/**
 * @brief Test the creation of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_create(c_str fail_message);

/**
 * @brief Test getting the c_str
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_c_str(c_str fail_message);

/**
 * @brief Test getting the length of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_length(c_str fail_message);

/**
 * @brief Test getting the capacity of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_capacity(c_str fail_message);

/**
 * @brief Test prepending a string to a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_prepend(c_str fail_message);

/**
 * @brief Test appending a string to a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_append(c_str fail_message);

/**
 * @brief Test pushing a string to a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_push(c_str fail_message);

/**
 * @brief Test checking if a string contains a substring
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_contains(c_str fail_message);

/**
 * @brief Test finding a substring in a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_find(c_str fail_message);

/**
 * @brief Test finding all instances of a substring in a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_find_all(c_str fail_message);

/**
 * @brief Test replacing a substring in a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_replace(c_str fail_message);

/**
 * @brief Test splitting a string into an array of strings
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_split(c_str fail_message);

/**
 * @brief Test the destruction of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_destroy(c_str fail_message);

/**
 * @brief Test the destruction of an array of strings
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_strings_destroy(c_str fail_message);

/**
 * @brief Add String tests to a test suite
 * @param test_suite The test suite to add the tests to
 * @return The result of the operation
 */
BasecTestResult test_string_add_tests(BasecTestSuite* test_suite);

#endif