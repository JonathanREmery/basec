/**
 * @file basec_array.h
 * @brief Implementation of an Array type and functions
 */
#ifndef BASEC_ARRAY_H
#define BASEC_ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * @brief Array structure
 */
typedef struct {
    size_t size;         //< The size of the array
    size_t element_size; //< The size of the elements in the array
    size_t capacity;     //< The capacity of the array
    void* data;          //< The data of the array
} Array;

/**
 * @brief Result of an array operation
 */
typedef enum {
    ARRAY_SUCCESS,                     //< The operation was successful
    ARRAY_ERROR_NULL_POINTER,          //< A NULL pointer was passed to the function
    ARRAY_ERROR_INVALID_CAPACITY,      //< The capacity is invalid
    ARRAY_ERROR_INVALID_ELEMENT_SIZE,  //< The element size is invalid
    ARRAY_ERROR_MALLOC,                //< The memory allocation failed
    ARRAY_ERROR_FULL,                  //< The array is full
    ARRAY_ERROR_OUT_OF_BOUNDS,         //< The index is out of bounds
    ARRAY_ERROR_MEMMOVE,               //< The memory move failed
    ARRAY_ERROR_EMPTY,                 //< The array is empty
    ARRAY_ERROR_NOT_FOUND              //< The element was not found in the array
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
 * @param element_size The size of the elements in the array
 * @param array_out The output array
 * @return The result of the operation
 */
ArrayResult array_create(size_t capacity, size_t element_size, Array** array_out);

/**
 * @brief Get the size of an array
 * 
 * @param array The array to get the size of
 * @param size_out The output size
 * @return The result of the operation
 */
ArrayResult array_size(Array* array, size_t* size_out);

/**
 * @brief Get the capacity of an array
 * 
 * @param array The array to get the capacity of
 * @param capacity_out The output capacity
 * @return The result of the operation
 */
ArrayResult array_capacity(Array* array, size_t* capacity_out);

/**
 * @brief Add an element to the array
 * 
 * @param array The array to add the element to
 * @param element The element to add
 * @return The result of the operation
 */
ArrayResult array_add(Array* array, void* element);

/**
 * @brief Remove an element from the array
 * 
 * @param array The array to remove the element from
 * @param index The index of the element to remove
 * @return The result of the operation
 */
ArrayResult array_remove(Array* array, uint64_t index);

/**
 * @brief Get an element from the array
 * 
 * @param array The array to get the element from
 * @param index The index of the element to get
 * @param element_out The output element
 * @return The result of the operation
 */
ArrayResult array_get(Array* array, uint64_t index, void* element_out);

/**
 * @brief Set an element in the array
 * 
 * @param array The array to set the element in
 * @param index The index of the element to set
 * @param element The element to set
 */
ArrayResult array_set(Array* array, uint64_t index, void* element);

/**
 * @brief Check if the array contains an element
 * 
 * @param array The array to check
 * @param element The element to check for
 * @return The result of the operation
 */
ArrayResult array_contains(Array* array, void* element);

/**
 * @brief Get the index of an element in the array
 * 
 * @param array The array to get the index of
 * @param element The element to get the index of
 * @param index_out The output index
 * @return The result of the operation
 */
ArrayResult array_index_of(Array* array, void* element, uint64_t* index_out);

/**
 * @brief Destroy an array
 * 
 * @param array_ptr A pointer to the array to destroy
 * @return The result of the operation
 */
ArrayResult array_destroy(Array** array_ptr);

#endif