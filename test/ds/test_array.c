/**
 * @file test_array.c
 * @brief Test the array implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "ds/array/basec_array.h"

/**
 * @brief Test the array_create function
 * 
 * @return void
 */
void test_array_create() {
    // Create a valid array
    Array* arr_valid = NULL;
    ArrayResult result_create_valid = array_create(10, &arr_valid);

    // Create an invalid array
    Array* arr_invalid = NULL;
    ArrayResult result_create_invalid = array_create(0, NULL);

    // Check the creation results
    assert(result_create_valid == ARRAY_SUCCESS);
    assert(result_create_invalid == ARRAY_ERROR_NULL_POINTER);
    assert(arr_valid != NULL);
    assert(arr_invalid == NULL);

    // Check the array properties
    assert(arr_valid->size == 0);
    assert(arr_valid->capacity == 10);
    assert(arr_valid->data != NULL);

    // Destroy the array
    array_destroy(&arr_valid);
}

/**
 * @brief Test the array_destroy function
 * 
 * @return void
 */
void test_array_destroy() {
    // Create a new array
    Array* arr = NULL;
    ArrayResult result_create = array_create(10, &arr);

    // Destroy the array
    ArrayResult result_destroy = array_destroy(&arr);
    assert(result_create == ARRAY_SUCCESS);
    assert(result_destroy == ARRAY_SUCCESS);

    // Try to destroy the array again
    ArrayResult result_destroy_again = array_destroy(&arr);
    assert(result_destroy_again == ARRAY_ERROR_NULL_POINTER);
}

/**
 * @brief Test the array implementation
 * 
 * @return int
 */
int main() {
    printf("[basec_array] Running tests...\n");

    // Run tests
    test_array_create();
    test_array_destroy();

    printf("[basec_array] All tests passed!\n");

    return 0;
}
