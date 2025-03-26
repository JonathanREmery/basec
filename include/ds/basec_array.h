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
 * @struct Array
 * @brief A dynamic array implementation
 */
typedef struct {
    void* data;
    u64   element_size;
    u64   length;
    u64   capacity;
} Array;

/**
 * @enum ArrayResult
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
} ArrayResult;

/**
 * @brief Handle the result of an array operation
 * @param result The result of the operation
 * @return The result of the operation
 */
void basec_array_handle_result(ArrayResult result);

/**
 * @brief Create an array
 * @param array The array to create
 * @param element_size The size of the elements in the array
 * @param capacity The capacity of the array
 */
ArrayResult basec_array_create(Array** array, u64 element_size, u64 capacity);

/**
 * @brief Push an element to the array
 * @param array The array to push to
 * @param element The element to push
 * @return The result of the operation
 */
ArrayResult basec_array_push(Array* array, void* element);

/**
 * @brief Pop an element from the array
 * @param array The array to pop from
 * @param element_out The element to pop
 * @return The result of the operation
 */
ArrayResult basec_array_pop(Array* array, void* element_out);

/**
 * @brief Destroy an array
 * @param array The array to destroy
 */
ArrayResult basec_array_destroy(Array** array);

#endif
