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
    String* str = string_create("Hello, World!");

    // Check if the string was created successfully
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
    String* str = string_create("Hello, World!");

    // Check the length of the string
    assert(string_length(str) == 13);

    // Destroy the string
    string_destroy(str);
}

/**
 * @brief Test the string_destroy function
 * 
 * @return void
 */
void test_string_destroy() {
    // Create a new string
    String* str = string_create("Hello, World!");

    // Destroy the string
    string_destroy(str);
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
    test_string_destroy();

    printf("[basec_string] All tests passed!\n");

    return 0;
}