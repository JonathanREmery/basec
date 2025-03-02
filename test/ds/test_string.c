/**
 * @file test_string.c
 * @brief Test the string implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "ds/basec_string.h"

/**
 * @brief Test the string_create function
 * 
 * @return void
 */
void test_string_create() {
    printf("  Testing string_create...\n");

    // Test valid creation
    String* str_valid = NULL;
    StringResult result_create_valid = string_create(
        "Hello, World!",
        32,
        &str_valid
    );
    assert(result_create_valid == STRING_SUCCESS);
    assert(str_valid != NULL);
    assert(strcmp(str_valid->data, "Hello, World!") == 0);
    assert(str_valid->length == 13);
    assert(str_valid->capacity == 32);

    // Test empty string
    printf("    Testing empty string...\n");
    String* str_empty = NULL;
    StringResult result_create_empty = string_create("", 16, &str_empty);
    assert(result_create_empty == STRING_SUCCESS);
    assert(str_empty != NULL);
    assert(str_empty->length == 0);
    assert(str_empty->capacity == 16);

    // Test NULL string data
    printf("    Testing NULL string data...\n");
    String* str_null = NULL;
    StringResult result_create_null_str = string_create(NULL, 32, &str_null);
    assert(result_create_null_str == STRING_ERROR_NULL_POINTER);
    assert(str_null == NULL);

    // Test NULL string output
    printf("    Testing NULL string output...\n");
    StringResult result_create_null_out = string_create("Hello", 32, NULL);
    assert(result_create_null_out == STRING_ERROR_NULL_POINTER);

    // Test minimum capacity
    printf("    Testing minimum capacity...\n");
    String* str_min = NULL;
    StringResult result_create_min = string_create("Hi", 3, &str_min);
    assert(result_create_min == STRING_SUCCESS);
    assert(str_min->capacity == 3);
    assert(str_min->length == 2);

    // Manual cleanup
    free(str_valid->data);
    free(str_valid);
    free(str_empty->data);
    free(str_empty);
    free(str_min->data);
    free(str_min);
}

/**
 * @brief Test the string_set function
 * 
 * @return void
 */
void test_string_set() {
    printf("  Testing string_set...\n");

    // Create string manually
    String* str = malloc(sizeof(String));
    str->data = malloc(32);
    strcpy(str->data, "");
    str->length = 0;
    str->capacity = 32;

    // Test setting string
    printf("    Testing setting string...\n");
    StringResult result_set = string_set(str, "Hello, World!");
    assert(result_set == STRING_SUCCESS);
    assert(strcmp(str->data, "Hello, World!") == 0);
    assert(str->length == 13);

    // Test setting different value
    printf("    Testing setting different value...\n");
    StringResult result_set_different = string_set(str, "Goodbye");
    assert(result_set_different == STRING_SUCCESS);
    assert(strcmp(str->data, "Goodbye") == 0);
    assert(str->length == 7);

    // Test setting same value
    printf("    Testing setting same value...\n");
    StringResult result_set_same = string_set(str, "Goodbye");
    assert(result_set_same == STRING_SUCCESS);
    assert(strcmp(str->data, "Goodbye") == 0);

    // Test NULL string pointer
    printf("    Testing NULL string pointer...\n");
    StringResult result_null_str = string_set(NULL, "Hello");
    assert(result_null_str == STRING_ERROR_NULL_POINTER);

    // Test NULL string value
    printf("    Testing NULL string value...\n");
    StringResult result_null_value = string_set(str, NULL);
    assert(result_null_value == STRING_ERROR_NULL_POINTER);

    // Manual cleanup
    free(str->data);
    free(str);
}

/**
 * @brief Test the string_length function
 * 
 * @return void
 */
void test_string_length() {
    printf("  Testing string_length...\n");

    // Create string manually
    String* str = malloc(sizeof(String));
    str->data = malloc(32);
    strcpy(str->data, "Hello, World!");
    str->length = 13;
    str->capacity = 32;

    // Test length retrieval
    printf("    Testing length retrieval...\n");
    size_t length = 0;
    StringResult result_length = string_length(str, &length);
    assert(result_length == STRING_SUCCESS);
    assert(length == 13);

    // Test zero length
    printf("    Testing zero length...\n");
    str->length = 0;
    result_length = string_length(str, &length);
    assert(result_length == STRING_SUCCESS);
    assert(length == 0);

    // Test NULL string pointer
    printf("    Testing NULL string pointer...\n");
    StringResult result_null_str = string_length(NULL, &length);
    assert(result_null_str == STRING_ERROR_NULL_POINTER);

    // Test NULL length output
    printf("    Testing NULL length output...\n");
    StringResult result_null_out = string_length(str, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Manual cleanup
    free(str->data);
    free(str);
}

/**
 * @brief Test the string_copy function
 * 
 * @return void
 */
void test_string_copy() {
    printf("  Testing string_copy...\n");

    // Create string manually
    String* str = malloc(sizeof(String));
    str->data = malloc(32);
    strcpy(str->data, "Hello, World!");
    str->length = 13;
    str->capacity = 32;

    // Test copying string
    printf("    Testing copying string...\n");
    String* str_copy = NULL;
    StringResult result_copy = string_copy(str, &str_copy);
    assert(result_copy == STRING_SUCCESS);
    assert(str_copy != NULL);
    assert(strcmp(str_copy->data, "Hello, World!") == 0);
    assert(str_copy->length == 13);

    // Test copying empty string
    printf("    Testing copying empty string...\n");
    str->length = 0;
    strcpy(str->data, "");
    String* empty_copy = NULL;
    StringResult result_empty = string_copy(str, &empty_copy);
    assert(result_empty == STRING_SUCCESS);
    assert(empty_copy->length == 0);

    // Test NULL string input
    printf("    Testing NULL string input...\n");
    String* null_copy = NULL;
    StringResult result_null_str = string_copy(NULL, &null_copy);
    assert(result_null_str == STRING_ERROR_NULL_POINTER);

    // Test NULL string output
    printf("    Testing NULL string output...\n");
    StringResult result_null_out = string_copy(str, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Manual cleanup
    free(str->data);
    free(str);
    free(str_copy->data);
    free(str_copy);
    free(empty_copy->data);
    free(empty_copy);
}

/**
 * @brief Test the string_concat function
 * 
 * @return void
 */
void test_string_concat() {
    printf("  Testing string_concat...\n");

    // Create str1 manually
    String* str1 = malloc(sizeof(String));
    str1->data = malloc(16);
    strcpy(str1->data, "Hello, ");
    str1->length = 7;
    str1->capacity = 16;

    // Create str2 manually
    String* str2 = malloc(sizeof(String));
    str2->data = malloc(16);
    strcpy(str2->data, "World!");
    str2->length = 6;
    str2->capacity = 16;

    // Test concatenation
    printf("    Testing concatenation...\n");
    String* str_concat = NULL;
    StringResult result_concat = string_concat(str1, str2, &str_concat);
    assert(result_concat == STRING_SUCCESS);
    assert(str_concat != NULL);
    assert(strcmp(str_concat->data, "Hello, World!") == 0);
    assert(str_concat->length == 13);

    // Test with empty string
    printf("    Testing with empty string...\n");
    str2->length = 0;
    strcpy(str2->data, "");
    String* str_concat_empty = NULL;
    StringResult result_empty = string_concat(str1, str2, &str_concat_empty);
    assert(result_empty == STRING_SUCCESS);
    assert(strcmp(str_concat_empty->data, "Hello, ") == 0);

    // Test NULL str1 pointer
    printf("    Testing NULL str1 pointer...\n");
    StringResult result_null_str1 = string_concat(NULL, str2, &str_concat);
    assert(result_null_str1 == STRING_ERROR_NULL_POINTER);

    // Test NULL str2 pointer
    printf("    Testing NULL str2 pointer...\n");
    StringResult result_null_str2 = string_concat(str1, NULL, &str_concat);
    assert(result_null_str2 == STRING_ERROR_NULL_POINTER);

    // Test NULL string output
    printf("    Testing NULL string output...\n");
    StringResult result_null_out = string_concat(str1, str2, NULL);
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Manual cleanup
    free(str1->data);
    free(str1);
    free(str2->data);
    free(str2);
    free(str_concat->data);
    free(str_concat);
    free(str_concat_empty->data);
    free(str_concat_empty);
}

/**
 * @brief Test the string_contains function
 * 
 * @return void
 */
void test_string_contains() {
    printf("  Testing string_contains...\n");

    // Create str_haystack manually
    String* str_haystack = malloc(sizeof(String));
    str_haystack->data = malloc(32);
    strcpy(str_haystack->data, "Hello, World!");
    str_haystack->length = 13;
    str_haystack->capacity = 32;

    // Create str_needle manually
    String* str_needle = malloc(sizeof(String));
    str_needle->data = malloc(16);
    strcpy(str_needle->data, "World");
    str_needle->length = 5;
    str_needle->capacity = 16;

    // Test contains
    printf("    Testing contains...\n");
    bool contains = false;
    StringResult result_contains = string_contains(
        str_haystack,
        str_needle,
        &contains
    );
    assert(result_contains == STRING_FOUND);
    assert(contains == true);

    // Test not contains
    printf("    Testing not contains...\n");
    strcpy(str_needle->data, "Goodbye");
    str_needle->length = 7;
    bool contains_missing = true;
    StringResult result_missing = string_contains(
        str_haystack,
        str_needle,
        &contains_missing
    );
    assert(result_missing == STRING_ERROR_NOT_FOUND);
    assert(contains_missing == false);

    // Test empty needle
    printf("    Testing empty needle...\n");
    str_needle->length = 0;
    strcpy(str_needle->data, "");
    bool contains_empty = true;
    StringResult result_empty = string_contains(
        str_haystack,
        str_needle,
        &contains_empty
    );
    assert(result_empty == STRING_ERROR_EMPTY);
    assert(contains_empty == false);

    // Test NULL str_haystack pointer
    printf("    Testing NULL str_haystack pointer...\n");
    StringResult result_null_haystack = string_contains(
        NULL,
        str_needle,
        &contains
    );
    assert(result_null_haystack == STRING_ERROR_NULL_POINTER);
    assert(contains == false);

    // Test NULL str_needle pointer
    printf("    Testing NULL str_needle pointer...\n");
    StringResult result_null_needle = string_contains(
        str_haystack,
        NULL,
        &contains
    );
    assert(result_null_needle == STRING_ERROR_NULL_POINTER);
    assert(contains == false);

    // Test NULL contains output
    printf("    Testing NULL contains output...\n");
    StringResult result_null_out = string_contains(
        str_haystack,
        str_needle,
        NULL
    );
    assert(result_null_out == STRING_ERROR_NULL_POINTER);

    // Manual cleanup
    free(str_haystack->data);
    free(str_haystack);
    free(str_needle->data);
    free(str_needle);
}

/**
 * @brief Test the string_index_of function
 * 
 * @return void
 */
void test_string_index_of() {
    printf("  Testing string_index_of...\n");

    // Create str_haystack manually
    String* str_haystack = malloc(sizeof(String));
    str_haystack->data = malloc(32);
    strcpy(str_haystack->data, "Hello, World!");
    str_haystack->length = 13;
    str_haystack->capacity = 32;

    // Create str_needle manually
    String* str_needle = malloc(sizeof(String));
    str_needle->data = malloc(16);
    strcpy(str_needle->data, "World");
    str_needle->length = 5;
    str_needle->capacity = 16;

    // Test finding index
    printf("    Testing finding index...\n");
    size_t index = 0;
    StringResult result_index = string_index_of(
        str_haystack,
        str_needle,
        &index
    );
    assert(result_index == STRING_FOUND);
    assert(index == 7);

    // Test not found
    printf("    Testing not found...\n");
    strcpy(str_needle->data, "Goodbye");
    str_needle->length = 7;
    StringResult result_missing = string_index_of(
        str_haystack,
        str_needle,
        &index
    );
    assert(result_missing == STRING_ERROR_NOT_FOUND);
    assert(index == __UINT64_MAX__);

    // Test empty needle
    printf("    Testing empty needle...\n");
    str_needle->length = 0;
    strcpy(str_needle->data, "");
    StringResult result_empty = string_index_of(
        str_haystack,
        str_needle,
        &index
    );
    assert(result_empty == STRING_ERROR_EMPTY);
    assert(index == __UINT64_MAX__);

    // Test NULL str_haystack pointer
    printf("    Testing NULL str_haystack pointer...\n");
    StringResult result_null_haystack = string_index_of(
        NULL,
        str_needle,
        &index
    );
    assert(result_null_haystack == STRING_ERROR_NULL_POINTER);
    assert(index == __UINT64_MAX__);

    // Test NULL str_needle pointer
    printf("    Testing NULL str_needle pointer...\n");
    StringResult result_null_needle = string_index_of(
        str_haystack,
        NULL,
        &index
    );
    assert(result_null_needle == STRING_ERROR_NULL_POINTER);
    assert(index == __UINT64_MAX__);

    // Test NULL index output
    printf("    Testing NULL index output...\n");
    StringResult result_null_out = string_index_of(
        str_haystack,
        str_needle,
        NULL
    );
    assert(result_null_out == STRING_ERROR_NULL_POINTER);
    assert(index == __UINT64_MAX__);

    // Manual cleanup
    free(str_haystack->data);
    free(str_haystack);
    free(str_needle->data);
    free(str_needle);
}

/**
 * @brief Test the string_destroy function
 * 
 * @return void
 */
void test_string_destroy() {
    printf("  Testing string_destroy...\n");

    // Create str manually
    String* str = malloc(sizeof(String));
    str->data = malloc(32);
    strcpy(str->data, "Hello, World!");
    str->length = 13;
    str->capacity = 32;

    // Test destroy
    printf("    Testing destroy...\n");
    StringResult result_destroy = string_destroy(&str);
    assert(result_destroy == STRING_SUCCESS);
    assert(str == NULL);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    StringResult result_destroy_null = string_destroy(NULL);
    assert(result_destroy_null == STRING_ERROR_NULL_POINTER);
    assert(str == NULL);

    // Test double destroy
    printf("    Testing double destroy...\n");
    StringResult result_destroy_again = string_destroy(&str);
    assert(result_destroy_again == STRING_ERROR_NULL_POINTER);
    assert(str == NULL);
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

    printf("[basec_string] All tests passed!\n");

    return 0;
}
