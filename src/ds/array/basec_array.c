/**
 * @file basec_array.c
 * @brief Implementation of an Array type and functions
 */

#include "ds/array/basec_array.h"

/**
 * @brief Convert an ArrayResult to a string
 * 
 * @param result The ArrayResult to convert
 * @return A string representation of the ArrayResult
 */
const char* array_result_to_string(ArrayResult result) {
    switch (result) {
        case ARRAY_SUCCESS:
            return "ARRAY_SUCCESS";
        case ARRAY_ERROR_NULL_POINTER:
            return "ARRAY_ERROR_NULL_POINTER";
        case ARRAY_ERROR_MALLOC:
            return "ARRAY_ERROR_MALLOC";
        default:
            return "UNKNOWN_ARRAY_RESULT";
    }
}

/**
 * @brief Create an array
 * 
 * @param capacity The capacity of the array
 * @param array_out The output array
 * @return The result of the operation
 */
ArrayResult array_create(size_t capacity, Array** array_out) {
    // Check for NULL pointers
    if (array_out == NULL) {
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Allocate memory for the array
    Array* array = (Array*)malloc(sizeof(Array));
    if (array == NULL) {
        return ARRAY_ERROR_MALLOC;
    }

    // Set the array size and capacity
    array->size = 0;
    array->capacity = capacity;

    // Allocate memory for the data
    array->data = (void**)malloc(capacity * sizeof(void*));
    if (array->data == NULL) {
        free(array);
        array = NULL;

        return ARRAY_ERROR_MALLOC;
    }

    // Return the result
    *array_out = array;
    return ARRAY_SUCCESS;
}

/**
 * @brief Destroy an array
 * 
 * @param array_ptr A pointer to the array to destroy
 * @return The result of the operation
 */
ArrayResult array_destroy(Array** array_ptr) {
    // Check for NULL pointers
    if (array_ptr == NULL || *array_ptr == NULL) {
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Free the array data
    free((*array_ptr)->data);
    (*array_ptr)->data = NULL;

    // Free the array structure
    free(*array_ptr);
    *array_ptr = NULL;

    // Return the result
    return ARRAY_SUCCESS;
}