/**
 * @file test_array.c
 * @brief Test the array implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "ds/array/basec_array.h"

/**
 * @brief Test the array_create function
 * 
 * @return void
 */
void test_array_create() {
    printf("  Testing array_create...\n");

    // Create a valid array
    Array* arr_valid = NULL;
    ArrayResult result_create_valid = array_create(10, sizeof(int), &arr_valid);

    // Test invalid capacity
    Array* arr_invalid_capacity = NULL;
    ArrayResult result_create_invalid_capacity = array_create(0, sizeof(int), &arr_invalid_capacity);

    // Test invalid element size
    Array* arr_invalid_elem_size = NULL;
    ArrayResult result_create_invalid_elem_size = array_create(10, 0, &arr_invalid_elem_size);
    
    // Test NULL output pointer
    ArrayResult result_create_null_out = array_create(10, sizeof(int), NULL);

    // Check the creation results
    assert(result_create_valid == ARRAY_SUCCESS);
    assert(result_create_invalid_capacity == ARRAY_ERROR_INVALID_CAPACITY);
    assert(arr_valid != NULL);
    assert(arr_invalid_capacity == NULL);
    assert(result_create_invalid_elem_size == ARRAY_ERROR_INVALID_ELEMENT_SIZE);
    assert(arr_invalid_elem_size == NULL);
    assert(result_create_null_out == ARRAY_ERROR_NULL_POINTER);

    // Check the array properties
    assert(arr_valid->size == 0);
    assert(arr_valid->capacity == 10);
    assert(arr_valid->element_size == sizeof(int));
    assert(arr_valid->data != NULL);

    // Test with different data types
    Array* arr_char = NULL;
    ArrayResult result_create_char = array_create(5, sizeof(char), &arr_char);
    assert(result_create_char == ARRAY_SUCCESS);
    assert(arr_char->element_size == sizeof(char));
    
    Array* arr_double = NULL;
    ArrayResult result_create_double = array_create(5, sizeof(double), &arr_double);
    assert(result_create_double == ARRAY_SUCCESS);
    assert(arr_double->element_size == sizeof(double));

    // Destroy the arrays
    array_destroy(&arr_valid);
    array_destroy(&arr_char);
    array_destroy(&arr_double);
}

/**
 * @brief Test the array_size function
 * 
 * @return void
 */
void test_array_size() {
    printf("  Testing array_size...\n");

    // Create a new array
    Array* arr = NULL;
    ArrayResult result_create = array_create(10, sizeof(int), &arr);

    // Check if the array was created successfully
    assert(result_create == ARRAY_SUCCESS);

    // Get the size of the array
    size_t size = 0;
    ArrayResult result_size = array_size(arr, &size);

    // Check if the size was retrieved successfully
    assert(result_size == ARRAY_SUCCESS);
    assert(size == 0);
    
    // Test with NULL pointer
    ArrayResult result_size_null = array_size(NULL, &size);
    assert(result_size_null == ARRAY_ERROR_NULL_POINTER);

    // Destroy the array
    array_destroy(&arr);
}

/**
 * @brief Test the array_capacity function
 * 
 * @return void
 */
void test_array_capacity() {
    printf("  Testing array_capacity...\n");
    
    // Create a new array
    Array* arr = NULL;
    ArrayResult result_create = array_create(10, sizeof(int), &arr);

    // Check if the array was created successfully
    assert(result_create == ARRAY_SUCCESS);

    // Get the capacity of the array
    size_t capacity = 0;
    ArrayResult result_capacity = array_capacity(arr, &capacity);

    // Check if the capacity was retrieved successfully
    assert(result_capacity == ARRAY_SUCCESS);
    assert(capacity == 10);
    
    // Test with different capacities
    Array* arr_large = NULL;
    array_create(1000, sizeof(int), &arr_large);

    // Get the capacity of the large array
    ArrayResult result_capacity_large = array_capacity(arr_large, &capacity);

    // Check if the capacity was retrieved successfully
    assert(result_capacity_large == ARRAY_SUCCESS);
    assert(capacity == 1000);
    
    // Test with NULL pointer
    ArrayResult result_capacity_null = array_capacity(NULL, &capacity);
    assert(result_capacity_null == ARRAY_ERROR_NULL_POINTER);

    // Destroy the arrays
    array_destroy(&arr);
    array_destroy(&arr_large);
}

/**
 * @brief Test the array_destroy function
 * 
 * @return void
 */
void test_array_destroy() {
    printf("  Testing array_destroy...\n");
    
    // Create a new array
    Array* arr = NULL;
    ArrayResult result_create = array_create(10, sizeof(int), &arr);

    // Destroy the array
    ArrayResult result_destroy = array_destroy(&arr);
    assert(result_create == ARRAY_SUCCESS);
    assert(result_destroy == ARRAY_SUCCESS);
    assert(arr == NULL);

    // Try to destroy the array again
    ArrayResult result_destroy_again = array_destroy(&arr);
    assert(result_destroy_again == ARRAY_ERROR_NULL_POINTER);
    
    // Test with NULL pointer
    ArrayResult result_destroy_null = array_destroy(NULL);
    assert(result_destroy_null == ARRAY_ERROR_NULL_POINTER);
}

/**
 * @brief Test the array_add function
 * 
 * @return void
 */
void test_array_add() {
    printf("  Testing array_add...\n");
    
    // Create a new array for integers
    Array* arr_int = NULL;
    array_create(5, sizeof(int), &arr_int);
    
    // Add elements to the array
    int values[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++) {
        // Add the element to the array
        ArrayResult result = array_add(arr_int, &values[i]);
        assert(result == ARRAY_SUCCESS);

        // Get the size of the array
        size_t size = 0;
        ArrayResult result_size = array_size(arr_int, &size);

        // Check if the size was retrieved successfully
        assert(result_size == ARRAY_SUCCESS);
        assert(size == (size_t)(i + 1));
    }
    
    // Try to add one more element when the array is full
    int extra_value = 60;
    ArrayResult result_full = array_add(arr_int, &extra_value);
    assert(result_full == ARRAY_ERROR_FULL);
    
    // Test with NULL pointers
    ArrayResult result_null_array = array_add(NULL, &values[0]);
    assert(result_null_array == ARRAY_ERROR_NULL_POINTER);
    
    ArrayResult result_null_element = array_add(arr_int, NULL);
    assert(result_null_element == ARRAY_ERROR_NULL_POINTER);
    
    // Test with different data types
    Array* arr_char = NULL;
    array_create(3, sizeof(char), &arr_char);
    
    char chars[] = {'A', 'B', 'C'};
    for (int i = 0; i < 3; i++) {
        ArrayResult result = array_add(arr_char, &chars[i]);
        assert(result == ARRAY_SUCCESS);
    }
    
    // Test with string
    Array* arr_string = NULL;
    array_create(2, sizeof(char*), &arr_string);
    
    char* str1 = "Hello";
    char* str2 = "World";
    
    // Add the elements to the array
    array_add(arr_string, &str1);
    array_add(arr_string, &str2);
    
    // Get the size of the array
    size_t size = 0;
    ArrayResult result_size = array_size(arr_string, &size);

    // Check if the size was retrieved successfully
    assert(result_size == ARRAY_SUCCESS);
    assert(size == 2);
    
    // Clean up
    array_destroy(&arr_int);
    array_destroy(&arr_char);
    array_destroy(&arr_string);
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
    test_array_size();
    test_array_capacity();
    test_array_add();
    test_array_destroy();

    printf("[basec_array] All tests passed!\n");

    return 0;
}
