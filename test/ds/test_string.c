/**
 * @file test_string.c
 * @brief Test the string implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "ds/basec_string.h"

/**
 * @brief Test the string_create function
 * 
 * @return void
 */
void test_string_create() {
    printf("  Testing string_create...\n");
    
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("Hello, World!", 32, &str);

    // Check if the string was created successfully
    assert(result_create == STRING_SUCCESS);
    assert(str != NULL);

    // Check string contents and length
    assert(strcmp(str->data, "Hello, World!") == 0);
    assert(str->length == 13);

    // Test with empty string
    String* empty_str = NULL;
    StringResult result_create_empty = string_create("", 16, &empty_str);
    assert(result_create_empty == STRING_SUCCESS);
    assert(empty_str != NULL);
    assert(empty_str->length == 0);
    assert(strcmp(empty_str->data, "") == 0);

    // Test with NULL parameters
    String* null_str = NULL;
    StringResult result_create_null_str = string_create(NULL, 0, &null_str);
    assert(result_create_null_str == STRING_ERROR_NULL_POINTER);
    assert(null_str == NULL);

    StringResult result_create_null_out = string_create("Hello", 16, NULL);
    assert(result_create_null_out == STRING_ERROR_NULL_POINTER);

    // Test with very long string
    char long_str_data[1024];
    memset(long_str_data, 'a', 1023);
    long_str_data[1023] = '\0';
    
    String* long_str = NULL;
    StringResult result_create_long = string_create(long_str_data, 2048, &long_str);
    assert(result_create_long == STRING_SUCCESS);
    assert(long_str != NULL);
    assert(long_str->length == 1023);

    // Destroy the strings
    string_destroy(&str);
    string_destroy(&empty_str);
    string_destroy(&long_str);
}

/**
 * @brief Test the string_set function
 * 
 * @return void
 */
void test_string_set() {
    printf("  Testing string_set...\n");
    
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("", 32, &str);

    // Set the string
    StringResult result_set = string_set(str, "Hello, World!");
    assert(result_create == STRING_SUCCESS);
    assert(result_set == STRING_SUCCESS);
    assert(strcmp(str->data, "Hello, World!") == 0);
    assert(str->length == 13);
    
    // Set the string to a different value
    StringResult result_set_different = string_set(str, "Goodbye, World!");
    assert(result_set_different == STRING_SUCCESS);
    assert(strcmp(str->data, "Goodbye, World!") == 0);
    assert(str->length == 15);

    // Test setting to the same value
    StringResult result_set_same = string_set(str, "Goodbye, World!");
    assert(result_set_same == STRING_SUCCESS);
    assert(strcmp(str->data, "Goodbye, World!") == 0);
    
    // Test setting to empty string
    StringResult result_set_empty = string_set(str, "");
    assert(result_set_empty == STRING_SUCCESS);
    assert(strcmp(str->data, "") == 0);
    assert(str->length == 0);
    
    // Test with NULL parameters
    StringResult result_null_str = string_set(NULL, "Hello");
    assert(result_null_str == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_value = string_set(str, NULL);
    assert(result_null_value == STRING_ERROR_NULL_POINTER);

    // Destroy the string
    string_destroy(&str);
}

/**
 * @brief Test the string_length function
 * 
 * @return void
 */
void test_string_length() {
    printf("  Testing string_length...\n");
    
    // Create strings of different lengths
    String* str_normal = NULL;
    String* str_empty = NULL;
    StringResult result_create_normal = string_create("Hello, World!", 32, &str_normal);
    StringResult result_create_empty = string_create("", 16, &str_empty);

    // Check the length of the normal string
    size_t length_normal = 0;
    StringResult result_length_normal = string_length(str_normal, &length_normal);
    assert(result_create_normal == STRING_SUCCESS);
    assert(result_length_normal == STRING_SUCCESS);
    assert(length_normal == 13);

    // Check the length of the empty string
    size_t length_empty = 0;
    StringResult result_length_empty = string_length(str_empty, &length_empty);
    assert(result_create_empty == STRING_SUCCESS);
    assert(result_length_empty == STRING_SUCCESS);
    assert(length_empty == 0);
    
    // Test with NULL parameters
    size_t length_null = 0;
    StringResult result_null_str = string_length(NULL, &length_null);
    assert(result_null_str == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_out = string_length(str_normal, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Destroy the strings
    string_destroy(&str_normal);
    string_destroy(&str_empty);
}

/**
 * @brief Test the string_copy function
 * 
 * @return void
 */
void test_string_copy() {
    printf("  Testing string_copy...\n");
    
    // Create strings to copy
    String* str_normal = NULL;
    String* str_empty = NULL;
    StringResult result_create_normal = string_create("Hello, World!", 32, &str_normal);
    StringResult result_create_empty = string_create("", 16, &str_empty);

    // Check creation results
    assert(result_create_normal == STRING_SUCCESS);
    assert(result_create_empty == STRING_SUCCESS);

    // Copy the normal string
    String* str_normal_copy = NULL;
    StringResult result_copy_normal = string_copy(str_normal, &str_normal_copy);

    // Check if the copy was created successfully
    assert(result_copy_normal == STRING_SUCCESS);
    assert(str_normal_copy != NULL);

    // Check if the copy is the same as the original
    assert(strcmp(str_normal_copy->data, str_normal->data) == 0);
    assert(str_normal_copy->length == str_normal->length);
    
    // Test that the strings are independent
    string_set(str_normal, "Modified");
    assert(strcmp(str_normal_copy->data, "Hello, World!") == 0);

    // Copy the empty string
    String* str_empty_copy = NULL;
    StringResult result_copy_empty = string_copy(str_empty, &str_empty_copy);
    assert(result_copy_empty == STRING_SUCCESS);
    assert(str_empty_copy != NULL);
    assert(str_empty_copy->length == 0);
    assert(strcmp(str_empty_copy->data, "") == 0);
    
    // Test with NULL parameters
    String* str_null_copy = NULL;
    StringResult result_null_str = string_copy(NULL, &str_null_copy);
    assert(result_null_str == STRING_ERROR_NULL_POINTER);
    assert(str_null_copy == NULL);
    
    StringResult result_null_out = string_copy(str_normal, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Destroy all strings
    string_destroy(&str_normal);
    string_destroy(&str_normal_copy);
    string_destroy(&str_empty);
    string_destroy(&str_empty_copy);
}

/**
 * @brief Test the string_concat function
 * 
 * @return void
 */
void test_string_concat() {
    printf("  Testing string_concat...\n");
    
    // Create strings to concatenate
    String* str1 = NULL;
    String* str2 = NULL;
    String* str_empty = NULL;
    StringResult result_create1 = string_create("Hello, ", 16, &str1);
    StringResult result_create2 = string_create("World!", 16, &str2);
    StringResult result_create_empty = string_create("", 16, &str_empty);

    // Check creation results
    assert(result_create1 == STRING_SUCCESS);
    assert(result_create2 == STRING_SUCCESS);
    assert(result_create_empty == STRING_SUCCESS);

    // Concatenate two non-empty strings
    String* str_concat = NULL;
    StringResult result_concat = string_concat(str1, str2, &str_concat);

    // Check if the concatenation was created successfully
    assert(result_concat == STRING_SUCCESS);
    assert(str_concat != NULL);

    // Check concatenation result
    assert(str_concat->length == 13);
    assert(strcmp(str_concat->data, "Hello, World!") == 0);
    
    // Test concatenation with empty string
    String* str_concat_empty = NULL;
    StringResult result_concat_empty = string_concat(str1, str_empty, &str_concat_empty);
    assert(result_concat_empty == STRING_SUCCESS);
    assert(str_concat_empty != NULL);
    assert(str_concat_empty->length == str1->length);
    assert(strcmp(str_concat_empty->data, str1->data) == 0);
    
    // Test with NULL parameters
    String* str_concat_null = NULL;
    StringResult result_null_str1 = string_concat(NULL, str2, &str_concat_null);
    assert(result_null_str1 == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_str2 = string_concat(str1, NULL, &str_concat_null);
    assert(result_null_str2 == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_out = string_concat(str1, str2, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Destroy the strings
    string_destroy(&str1);
    string_destroy(&str2);
    string_destroy(&str_empty);
    string_destroy(&str_concat);
    string_destroy(&str_concat_empty);
}

/**
 * @brief Test the string_contains function
 * 
 * @return void
 */
void test_string_contains() {
    printf("  Testing string_contains...\n");
    
    // Create test strings
    String* str_haystack = NULL;
    String* str_needle = NULL;
    String* str_missing = NULL;
    String* str_empty = NULL;
    
    string_create("Hello, World!", 32, &str_haystack);
    string_create("World", 16, &str_needle);
    string_create("Goodbye", 16, &str_missing);
    string_create("", 16, &str_empty);
    
    // Test substring is contained
    bool contains = false;
    StringResult result_contains = string_contains(str_haystack, str_needle, &contains);
    assert(result_contains == STRING_SUCCESS);
    assert(contains == true);
    
    // Test substring is not contained
    bool contains_missing = true;
    StringResult result_missing = string_contains(str_haystack, str_missing, &contains_missing);
    assert(result_missing == STRING_ERROR_NOT_FOUND);
    assert(contains_missing == false);
    
    // Test with empty substring
    bool contains_empty = false;
    StringResult result_empty = string_contains(str_haystack, str_empty, &contains_empty);
    assert(result_empty == STRING_ERROR_EMPTY);
    
    // Test with NULL parameters
    bool contains_null = false;
    StringResult result_null_haystack = string_contains(NULL, str_needle, &contains_null);
    assert(result_null_haystack == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_needle = string_contains(str_haystack, NULL, &contains_null);
    assert(result_null_needle == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_out = string_contains(str_haystack, str_needle, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Destroy the strings
    string_destroy(&str_haystack);
    string_destroy(&str_needle);
    string_destroy(&str_missing);
    string_destroy(&str_empty);
}

/**
 * @brief Test the string_index_of function
 * 
 * @return void
 */
void test_string_index_of() {
    printf("  Testing string_index_of...\n");
    
    // Create test strings
    String* str_haystack = NULL;
    String* str_needle = NULL;
    String* str_missing = NULL;
    String* str_empty = NULL;
    String* str_multiple = NULL;
    
    string_create("Hello, World!", 32, &str_haystack);
    string_create("World", 16, &str_needle);
    string_create("Goodbye", 16, &str_missing);
    string_create("", 16, &str_empty);
    string_create("Hello, Hello, Hello!", 32, &str_multiple);

    // Test substring is found
    size_t index = 0;
    StringResult result_index_of = string_index_of(str_haystack, str_needle, &index);
    assert(result_index_of == STRING_SUCCESS);
    assert(index == 7);

    // Test substring is not found
    size_t index_missing = 0;
    StringResult result_index_missing = string_index_of(str_haystack, str_missing, &index_missing);
    assert(result_index_missing == STRING_ERROR_NOT_FOUND);
    
    // Test with empty substring
    size_t index_empty = 0;
    StringResult result_empty = string_index_of(str_haystack, str_empty, &index_empty);
    assert(result_empty == STRING_ERROR_EMPTY);
    
    // Test finding first occurrence of multiple matches
    size_t index_multiple = 0;
    String* str_hello = NULL;
    string_create("Hello", 16, &str_hello);
    
    StringResult result_multiple = string_index_of(str_multiple, str_hello, &index_multiple);
    assert(result_multiple == STRING_SUCCESS);
    assert(index_multiple == 0);  // Should find first occurrence
    
    // Test with NULL parameters
    size_t index_null = 0;
    StringResult result_null_haystack = string_index_of(NULL, str_needle, &index_null);
    assert(result_null_haystack == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_needle = string_index_of(str_haystack, NULL, &index_null);
    assert(result_null_needle == STRING_ERROR_NULL_POINTER);
    
    StringResult result_null_out = string_index_of(str_haystack, str_needle, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Destroy the strings
    string_destroy(&str_haystack);
    string_destroy(&str_needle);
    string_destroy(&str_missing);
    string_destroy(&str_empty);
    string_destroy(&str_multiple);
    string_destroy(&str_hello);
}

/**
 * @brief Test the string_destroy function
 * 
 * @return void
 */
void test_string_destroy() {
    printf("  Testing string_destroy...\n");
    
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("Hello, World!", 32, &str);

    // Destroy the string
    StringResult result_destroy = string_destroy(&str);
    assert(result_create == STRING_SUCCESS);
    assert(result_destroy == STRING_SUCCESS);
    assert(str == NULL);

    // Try to destroy the string again
    StringResult result_destroy_again = string_destroy(&str);
    assert(result_destroy_again == STRING_ERROR_NULL_POINTER);
    
    // Test with NULL pointer
    StringResult result_destroy_null = string_destroy(NULL);
    assert(result_destroy_null == STRING_ERROR_NULL_POINTER);
}

/**
 * @brief Test the string_result_to_string function
 * 
 * @return void
 */
void test_string_result_to_string() {
    printf("  Testing string_result_to_string...\n");
    
    // Test all result codes
    assert(strcmp(string_result_to_string(STRING_SUCCESS), "STRING_SUCCESS") == 0);
    assert(strcmp(string_result_to_string(STRING_ERROR_NULL_POINTER), "STRING_ERROR_NULL_POINTER") == 0);
    assert(strcmp(string_result_to_string(STRING_ERROR_MALLOC), "STRING_ERROR_MALLOC") == 0);
    assert(strcmp(string_result_to_string(STRING_ERROR_REALLOC), "STRING_ERROR_REALLOC") == 0);
    assert(strcmp(string_result_to_string(STRING_ERROR_EMPTY), "STRING_ERROR_EMPTY") == 0);
    assert(strcmp(string_result_to_string(STRING_ERROR_NOT_FOUND), "STRING_ERROR_NOT_FOUND") == 0);
    
    // Test an unknown result code
    assert(strcmp(string_result_to_string(999), "UNKNOWN_STRING_RESULT") == 0);
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
    test_string_set();
    test_string_length();
    test_string_copy();
    test_string_concat();
    test_string_contains();
    test_string_index_of();
    test_string_destroy();
    test_string_result_to_string();

    printf("[basec_string] All tests passed!\n");

    return 0;
}