/**
 * @file basec_array.h
 * @brief A dynamic array implementation
 */
#ifndef BASEC_ARRAY_H
#define BASEC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basec_types.h"

/**
 * @struct BasecArray
 * @brief A dynamic array implementation
 */
typedef struct {
    void* data;
    u64   element_size;
    u64   length;
    u64   capacity;
} BasecArray;

/**
 * @enum BasecArrayResult
 * @brief The result of an array operation
 */
typedef enum {
    BASEC_ARRAY_SUCCESS,
    BASEC_ARRAY_NULL_POINTER,
    BASEC_ARRAY_INVALID_ELEMENT_SIZE,
    BASEC_ARRAY_INVALID_CAPACITY,
    BASEC_ARRAY_ALLOCATION_FAILURE,
    BASEC_ARRAY_MEMOP_FAILURE,
    BASEC_ARRAY_EMPTY,
    BASEC_ARRAY_OUT_OF_BOUNDS,
    BASEC_ARRAY_NOT_FOUND,
} BasecArrayResult;

/**
 * @brief Handle the result of an array operation
 * @param result The result of the operation
 * @return The result of the operation
 */
void basec_array_handle_result(BasecArrayResult result);

/**
 * @brief Create an array
 * @param array The array to create
 * @param element_size The size of the elements in the array
 * @param capacity The capacity of the array
 */
BasecArrayResult basec_array_create(
    BasecArray** array, 
    u64 element_size, 
    u64 capacity
);

/**
 * @brief Push an element to the array
 * @param array The array to push to
 * @param element The element to push
 * @return The result of the operation
 */
BasecArrayResult basec_array_push(BasecArray* array, void* element);

/**
 * @brief Append an element to the array (same as push)
 * @param array The array to append to
 * @param element The element to append
 * @return The result of the operation
 */
BasecArrayResult basec_array_append(BasecArray* array, void* element);

/**
 * @brief Pop an element from the array
 * @param array The array to pop from
 * @param element_out The element to pop
 * @return The result of the operation
 */
BasecArrayResult basec_array_pop(BasecArray* array, void* element_out);

/**
 * @brief Get an element from the array
 * @param array The array to get from
 * @param index The index of the element to get
 * @param element_out The element to get
 * @return The result of the operation
 */
BasecArrayResult basec_array_get(BasecArray* array, u64 index, void* element_out);

/**
 * @brief Set an element in the array
 * @param array The array to set in
 * @param index The index of the element to set
 * @param element The element to set
 * @return The result of the operation
 */
BasecArrayResult basec_array_set(BasecArray* array, u64 index, void* element);

/**
 * @brief Check if the array contains an element
 * @param array The array to check
 * @param element The element to check
 * @param contains_out The result of the operation
 * @return The result of the operation
 */
BasecArrayResult basec_array_contains(BasecArray* array, void* element, bool* contains_out);

/**
 * @brief Find the index of an element in the array
 * @param array The array to find from
 * @param element The element to find
 * @param index_out The index of the element to find
 * @return The result of the operation
 */
BasecArrayResult basec_array_find(BasecArray* array, void* element, u64* index_out);

/**
 * @brief Destroy an array
 * @param array The array to destroy
 */
BasecArrayResult basec_array_destroy(BasecArray** array);

#endif
