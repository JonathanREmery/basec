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
        case ARRAY_ERROR_INVALID_CAPACITY:
            return "ARRAY_ERROR_INVALID_CAPACITY";
        case ARRAY_ERROR_INVALID_ELEMENT_SIZE:
            return "ARRAY_ERROR_INVALID_ELEMENT_SIZE";
        case ARRAY_ERROR_MALLOC:
            return "ARRAY_ERROR_MALLOC";
        case ARRAY_ERROR_FULL:
            return "ARRAY_ERROR_FULL";
        default:
            return "UNKNOWN_ARRAY_RESULT";
    }
}

/**
 * @brief Create an array
 * 
 * @param capacity The capacity of the array
 * @param element_size The size of the elements in the array
 * @param array_out The output array
 * @return The result of the operation
 */
ArrayResult array_create(size_t capacity, size_t element_size, Array** array_out) {
    // Check if the capacity is valid
    if (capacity < 1) {
        return ARRAY_ERROR_INVALID_CAPACITY;
    }

    // Check if the element size is valid
    if (element_size < 1) {
        return ARRAY_ERROR_INVALID_ELEMENT_SIZE;
    }

    // Check for NULL pointers
    if (array_out == NULL) {
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Allocate memory for the array
    Array* array = (Array*)malloc(sizeof(Array));
    if (array == NULL) {
        return ARRAY_ERROR_MALLOC;
    }

    // Set the array size, element size, and capacity
    array->size = 0;
    array->element_size = element_size;
    array->capacity = capacity;

    // Allocate memory for the data
    array->data = malloc(element_size * capacity);
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
 * @brief Get the size of an array
 * 
 * @param array The array to get the size of
 * @param size_out The output size
 * @return The result of the operation
 */
ArrayResult array_size(Array* array, size_t* size_out) {
    // Check for NULL pointers
    if (array == NULL || size_out == NULL) {
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Return the size of the array
    *size_out = array->size;

    // Return the result
    return ARRAY_SUCCESS;
}

/**
 * @brief Get the capacity of an array
 * 
 * @param array The array to get the capacity of
 * @param capacity_out The output capacity
 * @return The result of the operation
 */
ArrayResult array_capacity(Array* array, size_t* capacity_out) {
    // Check for NULL pointers
    if (array == NULL || capacity_out == NULL) {
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Return the capacity of the array
    *capacity_out = array->capacity;

    // Return the result
    return ARRAY_SUCCESS;
}

/**
 * @brief Add an element to the array
 * 
 * @param array The array to add the element to
 * @param element The element to add
 * @return The result of the operation
 */
ArrayResult array_add(Array* array, void* element) {
    // Check for NULL pointers
    if (array == NULL || element == NULL) {
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Check if the array is full
    if (array->size >= array->capacity) {
        return ARRAY_ERROR_FULL;
    }

    // Add the element to the array
    memcpy(array->data + array->element_size * array->size, element, array->element_size);
    array->size++;

    // Return the result
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