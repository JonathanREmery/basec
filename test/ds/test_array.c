/**
 * @file test_array.c
 * @brief Test the array implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "ds/basec_array.h"

/**
 * @brief Test the array_create function
 * 
 * @return void
 */
void test_array_create() {
    printf("  Testing array_create...\n");

    // Test valid creation
    printf("    Testing valid creation...\n");
    Array* arr_valid = NULL;
    ArrayResult result_create_valid = array_create(sizeof(int), 10, &arr_valid);
    assert(result_create_valid == ARRAY_SUCCESS);
    assert(arr_valid != NULL);
    assert(arr_valid->element_size == sizeof(int));
    assert(arr_valid->capacity == 10);
    assert(arr_valid->size == 0);
    assert(arr_valid->data != NULL);

    // Test invalid element size
    printf("    Testing invalid element size...\n");
    Array* arr_invalid_elem_size = NULL;
    ArrayResult result_create_invalid_elem_size = array_create(
        0,
        10,
        &arr_invalid_elem_size
    );
    assert(result_create_invalid_elem_size == ARRAY_ERROR_INVALID_ELEMENT_SIZE);
    assert(arr_invalid_elem_size == NULL);

    // Test invalid capacity
    printf("    Testing invalid capacity...\n");
    Array* arr_invalid_capacity = NULL;
    ArrayResult result_create_invalid_capacity = array_create(
        sizeof(int),
        0,
        &arr_invalid_capacity
    );
    assert(result_create_invalid_capacity == ARRAY_ERROR_INVALID_CAPACITY);
    assert(arr_invalid_capacity == NULL);

    // Test NULL output pointer
    printf("    Testing NULL output pointer...\n");
    ArrayResult result_create_null_out = array_create(sizeof(int), 10, NULL);
    assert(result_create_null_out == ARRAY_ERROR_NULL_POINTER);

    // Test minimum capacity
    printf("    Testing minimum capacity...\n");
    Array* arr_min = NULL;
    ArrayResult result_create_min = array_create(sizeof(int), 1, &arr_min);
    assert(result_create_min == ARRAY_SUCCESS);
    assert(arr_min->capacity == 1);

    // Test large capacity
    printf("    Testing large capacity...\n");
    Array* arr_large = NULL;
    ArrayResult result_create_large = array_create(
        sizeof(int),
        1000,
        &arr_large
    );
    assert(result_create_large == ARRAY_SUCCESS);
    assert(arr_large->capacity == 1000);

    // Manual cleanup
    free(arr_valid->data);
    free(arr_valid);
    free(arr_min->data);
    free(arr_min);
    free(arr_large->data);
    free(arr_large);
}

/**
 * @brief Test the array_size function
 * 
 * @return void
 */
void test_array_size() {
    printf("  Testing array_size...\n");

    // Create array manually
    Array* arr = malloc(sizeof(Array));
    arr->size = 5;
    arr->capacity = 10;
    arr->element_size = sizeof(int);
    arr->data = malloc(sizeof(int) * 10);

    // Test valid size retrieval
    printf("    Testing valid size retrieval...\n");
    size_t size = 0;
    ArrayResult result_size = array_size(arr, &size);
    assert(result_size == ARRAY_SUCCESS);
    assert(size == 5);

    // Test zero size
    printf("    Testing zero size...\n");
    arr->size = 0;
    result_size = array_size(arr, &size);
    assert(result_size == ARRAY_SUCCESS);
    assert(size == 0);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    ArrayResult result_size_null = array_size(NULL, &size);
    assert(result_size_null == ARRAY_ERROR_NULL_POINTER);

    // Test NULL size_out
    printf("    Testing NULL size_out...\n");
    ArrayResult result_size_null_out = array_size(arr, NULL);
    assert(result_size_null_out == ARRAY_ERROR_NULL_POINTER);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_capacity function
 * 
 * @return void
 */
void test_array_capacity() {
    printf("  Testing array_capacity...\n");

    // Create array manually
    Array* arr = malloc(sizeof(Array));
    arr->capacity = 10;
    arr->size = 0;
    arr->element_size = sizeof(int);
    arr->data = malloc(sizeof(int) * 10);

    // Test valid capacity retrieval
    printf("    Testing valid capacity retrieval...\n");
    size_t capacity = 0;
    ArrayResult result_capacity = array_capacity(arr, &capacity);
    assert(result_capacity == ARRAY_SUCCESS);
    assert(capacity == 10);

    // Test different capacity
    printf("    Testing different capacity...\n");
    arr->capacity = 1000;
    result_capacity = array_capacity(arr, &capacity);
    assert(result_capacity == ARRAY_SUCCESS);
    assert(capacity == 1000);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    ArrayResult result_capacity_null = array_capacity(NULL, &capacity);
    assert(result_capacity_null == ARRAY_ERROR_NULL_POINTER);

    // Test NULL capacity_out
    printf("    Testing NULL capacity_out...\n");
    ArrayResult result_capacity_null_out = array_capacity(arr, NULL);
    assert(result_capacity_null_out == ARRAY_ERROR_NULL_POINTER);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_add function
 * 
 * @return void
 */
void test_array_add() {
    printf("  Testing array_add...\n");

    // Create array manually
    Array* arr = malloc(sizeof(Array));
    arr->element_size = sizeof(int);
    arr->capacity = 3;
    arr->size = 0;
    arr->data = malloc(sizeof(int) * 3);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    int value = 10;
    ArrayResult result_null_array = array_add(NULL, &value);
    assert(result_null_array == ARRAY_ERROR_NULL_POINTER);

    // Test NULL element
    printf("    Testing NULL element...\n");
    ArrayResult result_null_element = array_add(arr, NULL);
    assert(result_null_element == ARRAY_ERROR_NULL_POINTER);

    // Test adding elements
    printf("    Testing adding elements...\n");
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
      ArrayResult result = array_add(arr, &values[i]);
      assert(result == ARRAY_SUCCESS);
      assert(arr->size == (size_t)(i + 1));
    }

    // Test adding when full (triggers resize)
    printf("    Testing adding when full (triggers resize)...\n");
    int extra = 40;
    ArrayResult result_full = array_add(arr, &extra);
    assert(result_full == ARRAY_SUCCESS);
    assert(arr->size == 4);
    assert(arr->capacity == 6);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_remove function
 * 
 * @return void
 */
void test_array_remove() {
    printf("  Testing array_remove...\n");

    // Create array manually with elements
    Array* arr = malloc(sizeof(Array));
    arr->element_size = sizeof(int);
    arr->capacity = 5;
    arr->size = 5;
    arr->data = malloc(sizeof(int) * 5);
    int values[] = {10, 20, 30, 40, 50};
    memcpy(arr->data, values, sizeof(int) * 5);

    // Test removing from middle
    printf("    Testing removing from middle...\n");
    ArrayResult result_middle = array_remove(arr, 2);
    assert(result_middle == ARRAY_SUCCESS);
    assert(arr->size == 4);

    // Test removing from end
    printf("    Testing removing from end...\n");
    ArrayResult result_end = array_remove(arr, 3);
    assert(result_end == ARRAY_SUCCESS);
    assert(arr->size == 3);

    // Test removing from start
    printf("    Testing removing from start...\n");
    ArrayResult result_start = array_remove(arr, 0);
    assert(result_start == ARRAY_SUCCESS);
    assert(arr->size == 2);

    // Test invalid index
    printf("    Testing invalid index...\n");
    ArrayResult result_invalid = array_remove(arr, 5);
    assert(result_invalid == ARRAY_ERROR_OUT_OF_BOUNDS);

    // Test NULL array
    printf("    Testing NULL array...\n");
    ArrayResult result_null = array_remove(NULL, 0);
    assert(result_null == ARRAY_ERROR_NULL_POINTER);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_get function
 * 
 * @return void
 */
void test_array_get() {
    printf("  Testing array_get...\n");

    // Create array manually with elements
    Array* arr = malloc(sizeof(Array));
    arr->element_size = sizeof(int);
    arr->capacity = 5;
    arr->size = 3;
    arr->data = malloc(sizeof(int) * 5);
    int values[] = {10, 20, 30};
    memcpy(arr->data, values, sizeof(int) * 3);

    // Test getting valid element
    printf("    Testing getting valid element...\n");
    int value = 0;
    ArrayResult result_get = array_get(arr, 1, &value);
    assert(result_get == ARRAY_SUCCESS);
    assert(value == 20);

    // Test invalid index
    printf("    Testing invalid index...\n");
    ArrayResult result_invalid = array_get(arr, 3, &value);
    assert(result_invalid == ARRAY_ERROR_OUT_OF_BOUNDS);

    // Test NULL array
    printf("    Testing NULL array...\n");
    ArrayResult result_null_array = array_get(NULL, 0, &value);
    assert(result_null_array == ARRAY_ERROR_NULL_POINTER);

    // Test NULL element_out
    printf("    Testing NULL element_out...\n");
    ArrayResult result_null_element = array_get(arr, 0, NULL);
    assert(result_null_element == ARRAY_ERROR_NULL_POINTER);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_set function
 * 
 * @return void
 */
void test_array_set() {
    printf("  Testing array_set...\n");

    // Create array manually with elements
    Array* arr = malloc(sizeof(Array));
    arr->element_size = sizeof(int);
    arr->capacity = 5;
    arr->size = 3;
    arr->data = malloc(sizeof(int) * 5);
    int values[] = {10, 20, 30};
    memcpy(arr->data, values, sizeof(int) * 3);

    // Test setting valid element
    printf("    Testing setting valid element...\n");
    int new_value = 100;
    ArrayResult result_set = array_set(arr, 1, &new_value);
    assert(result_set == ARRAY_SUCCESS);

    // Test invalid index
    printf("    Testing invalid index...\n");
    ArrayResult result_invalid = array_set(arr, 3, &new_value);
    assert(result_invalid == ARRAY_ERROR_OUT_OF_BOUNDS);

    // Test NULL array
    printf("    Testing NULL array...\n");
    ArrayResult result_null_array = array_set(NULL, 0, &new_value);
    assert(result_null_array == ARRAY_ERROR_NULL_POINTER);

    // Test NULL element
    printf("    Testing NULL element...\n");
    ArrayResult result_null_element = array_set(arr, 0, NULL);
    assert(result_null_element == ARRAY_ERROR_NULL_POINTER);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_contains function
 * 
 * @return void
 */
void test_array_contains() {
    printf("  Testing array_contains...\n");

    // Create array manually with elements
    Array* arr = malloc(sizeof(Array));
    arr->element_size = sizeof(int);
    arr->capacity = 5;
    arr->size = 3;
    arr->data = malloc(sizeof(int) * 5);
    int values[] = {10, 20, 30};
    memcpy(arr->data, values, sizeof(int) * 3);

    // Test contains existing element
    printf("    Testing contains existing element...\n");
    ArrayResult result_contains = array_contains(arr, &values[1]);
    assert(result_contains == ARRAY_FOUND);

    // Test contains non-existing element
    printf("    Testing contains non-existing element...\n");
    int not_in_array = 40;
    ArrayResult result_not_in_array = array_contains(arr, &not_in_array);
    assert(result_not_in_array == ARRAY_ERROR_NOT_FOUND);

    // Test NULL array
    printf("    Testing NULL array...\n");
    ArrayResult result_null_array = array_contains(NULL, &values[0]);
    assert(result_null_array == ARRAY_ERROR_NULL_POINTER);

    // Test NULL element
    printf("    Testing NULL element...\n");
    ArrayResult result_null_element = array_contains(arr, NULL);
    assert(result_null_element == ARRAY_ERROR_NULL_POINTER);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_index_of function
 * 
 * @return void
 */
void test_array_index_of() {
    printf("  Testing array_index_of...\n");

    // Create array manually with elements
    Array* arr = malloc(sizeof(Array));
    arr->element_size = sizeof(int);
    arr->capacity = 5;
    arr->size = 3;
    arr->data = malloc(sizeof(int) * 5);
    int values[] = {10, 20, 30};
    memcpy(arr->data, values, sizeof(int) * 3);

    // Test finding index of existing element
    printf("    Testing finding index of existing element...\n");
    uint64_t index = 0;
    ArrayResult result_index = array_index_of(arr, &values[1], &index);
    assert(result_index == ARRAY_FOUND);
    assert(index == 1);

    // Test finding non-existing element
    printf("    Testing finding non-existing element...\n");
    int not_in_array = 40;
    ArrayResult result_not_in_array = array_index_of(arr, &not_in_array, &index);
    assert(result_not_in_array == ARRAY_ERROR_NOT_FOUND);

    // Test empty array
    printf("    Testing empty array...\n");
    arr->size = 0;
    ArrayResult result_empty = array_index_of(arr, &values[0], &index);
    assert(result_empty == ARRAY_ERROR_EMPTY);

    // Test NULL array
    printf("    Testing NULL array...\n");
    ArrayResult result_null_array = array_index_of(NULL, &values[0], &index);
    assert(result_null_array == ARRAY_ERROR_NULL_POINTER);

    // Test NULL element
    printf("    Testing NULL element...\n");
    ArrayResult result_null_element = array_index_of(arr, NULL, &index);
    assert(result_null_element == ARRAY_ERROR_NULL_POINTER);

    // Test NULL index_out
    printf("    Testing NULL index_out...\n");
    ArrayResult result_null_index = array_index_of(arr, &values[0], NULL);
    assert(result_null_index == ARRAY_ERROR_NULL_POINTER);

    // Manual cleanup
    free(arr->data);
    free(arr);
}

/**
 * @brief Test the array_destroy function
 * 
 * @return void
 */
void test_array_destroy() {
    printf("  Testing array_destroy...\n");

    // Create array manually
    Array* arr = malloc(sizeof(Array));
    arr->data = malloc(sizeof(int) * 10);
    arr->element_size = sizeof(int);
    arr->capacity = 10;
    arr->size = 0;

    // Test destroy
    printf("    Testing destroy...\n");
    ArrayResult result_destroy = array_destroy(&arr);
    assert(result_destroy == ARRAY_SUCCESS);
    assert(arr == NULL);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    ArrayResult result_destroy_null = array_destroy(NULL);
    assert(result_destroy_null == ARRAY_ERROR_NULL_POINTER);

    // Test double destroy
    printf("    Testing double destroy...\n");
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
    test_array_size();
    test_array_capacity();
    test_array_add();
    test_array_remove();
    test_array_get();
    test_array_set();
    test_array_contains();
    test_array_index_of();
    test_array_destroy();

    printf("[basec_array] All tests passed!\n");

    return 0;
}
