/**
 * @file basec_array.h
 * @brief Implementation of an Array type and functions
 */
#ifndef BASEC_ARRAY_H
#define BASEC_ARRAY_H

#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Array structure
 */
typedef struct {
    size_t size;     //< The size of the array
    size_t capacity; //< The capacity of the array
    void** data;     //< The data of the array
} Array;

/**
 * @brief Result of an array operation
 */
typedef enum {
    ARRAY_SUCCESS,            //< The operation was successful
    ARRAY_ERROR_NULL_POINTER, //< A NULL pointer was passed to the function
    ARRAY_ERROR_MALLOC        //< The memory allocation failed
} ArrayResult;

/**
 * @brief Convert an ArrayResult to a string
 * 
 * @param result The ArrayResult to convert
 * @return A string representation of the ArrayResult
 */
const char* array_result_to_string(ArrayResult result);

/**
 * @brief Create an array
 * 
 * @param capacity The capacity of the array
 * @param array_out The output array
 * @return The result of the operation
 */
ArrayResult array_create(size_t capacity, Array** array_out);

/**
 * @brief Destroy an array
 * 
 * @param array_ptr A pointer to the array to destroy
 * @return The result of the operation
 */
ArrayResult array_destroy(Array** array_ptr);

#endif