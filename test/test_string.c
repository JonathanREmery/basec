/**
 * @file test_string.c
 * @brief Test the string implementation
 */

#include <assert.h>
#include <stdio.h>

#include "basec_string.h"

/**
 * @brief Test the string_create function
 * 
 * @return void
 */
void test_string_create() {
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("Hello, World!", &str);

    // Check if the string was created successfully
    assert(result_create == STRING_SUCCESS);
    assert(str != NULL);

    // Check string contents and length
    assert(strcmp(str->data, "Hello, World!") == 0);
    assert(str->length == 13);

    // Destroy the string
    string_destroy(str);
}

/**
 * @brief Test the string_length function
 * 
 * @return void
 */
void test_string_length() {
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("Hello, World!", &str);

    // Check the length of the string
    size_t length = 0;
    StringResult result_length = string_length(str, &length);
    assert(result_create == STRING_SUCCESS);
    assert(result_length == STRING_SUCCESS);
    assert(length == 13);

    // Destroy the string
    string_destroy(str);
}

/**
 * @brief Test the string_copy function
 * 
 * @return void
 */
void test_string_copy() {
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("Hello, World!", &str);

    // Copy the string
    String* str_copy = NULL;
    StringResult result_copy = string_copy(str, &str_copy);

    // Check if the copy was created successfully
    assert(result_create == STRING_SUCCESS);
    assert(result_copy == STRING_SUCCESS);
    assert(str_copy != NULL);

    // Check if the copy is the same as the original
    assert(strcmp(str_copy->data, str->data) == 0);

    // Destroy the original string
    string_destroy(str);

    // Destroy the copy
    string_destroy(str_copy);
}

/**
 * @brief Test the string_concat function
 * 
 * @return void
 */
void test_string_concat() {
    // Create two strings
    String* str1 = NULL;
    String* str2 = NULL;
    StringResult result_create1 = string_create("Hello, ", &str1);
    StringResult result_create2 = string_create("World!", &str2);

    // Concatenate the strings
    String* str_concat = NULL;
    StringResult result_concat = string_concat(str1, str2, &str_concat);

    // Check if the concatenation was created successfully
    assert(result_create1 == STRING_SUCCESS);
    assert(result_create2 == STRING_SUCCESS);
    assert(result_concat == STRING_SUCCESS);
    assert(str_concat != NULL);

    // Check if the concatenation is the correct length
    assert(str_concat->length == 13);

    // Destroy the strings
    string_destroy(str1);
    string_destroy(str2);
    string_destroy(str_concat);
}

/**
 * @brief Test the string_destroy function
 * 
 * @return void
 */
void test_string_destroy() {
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("Hello, World!", &str);

    // Destroy the string
    StringResult result_destroy = string_destroy(str);
    assert(result_create == STRING_SUCCESS);
    assert(result_destroy == STRING_SUCCESS);
}

/**
 * @brief Test the string implementation
 * 
 * @return int
 */
int main() {
    printf("[basec_string] Running tests...\n");

    // Run tests
    test_string_create();
    test_string_length();
    test_string_copy();
    test_string_concat();
    test_string_destroy();

    printf("[basec_string] All tests passed!\n");

    return 0;
}