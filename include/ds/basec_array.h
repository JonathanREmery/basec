/**
 * @file basec_array.h
 * @brief Declaration of an Array type and functions
 */
#ifndef BASEC_ARRAY_H
#define BASEC_ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Array structure
 */
typedef struct {
    size_t element_size; //< Size of the elements in the array
    size_t capacity;     //< Capacity of the array
    size_t size;         //< Size of the array
    void*  data;         //< Data of the array
} Array;

/**
 * @brief Result of an array operation
 */
typedef enum {
    ARRAY_SUCCESS,                    //< Success
    ARRAY_ERROR_NULL_POINTER,         //< NULL pointer
    ARRAY_ERROR_INVALID_CAPACITY,     //< Invalid capacity
    ARRAY_ERROR_INVALID_ELEMENT_SIZE, //< Invalid element size
    ARRAY_ERROR_MALLOC,               //< Malloc failed
    ARRAY_ERROR_REALLOC,              //< Realloc failed
    ARRAY_ERROR_MEMCPY,               //< Memcpy failed
    ARRAY_ERROR_MEMMOVE,              //< Memmove failed
    ARRAY_ERROR_OUT_OF_BOUNDS,        //< Out of bounds
    ARRAY_ERROR_EMPTY,                //< Empty
    ARRAY_FOUND,                      //< Found
    ARRAY_ERROR_NOT_FOUND             //< Not found
} ArrayResult;

/**
 * @brief Convert an ArrayResult to a string
 * 
 * @param result ArrayResult to convert
 * @return       String representation of the ArrayResult
 */
const char* array_result_to_string(ArrayResult result);

/**
 * @brief Create an array
 * 
 * @param element_size Size of the elements in the array
 * @param capacity     Capacity of the array
 * @param array_out    Output array
 * @return             Result of the operation
 */
ArrayResult array_create(
    size_t element_size,
    size_t capacity,
    Array** array_out
);

/**
 * @brief Resize the capacity of an array
 * 
 * @param array        Array to resize
 * @param new_capacity New capacity
 * @return             Result of the operation
 */
ArrayResult array_resize(Array* array, size_t new_capacity);

/**
 * @brief Get the size of an array
 * 
 * @param array    Array to get the size of
 * @param size_out Output size
 * @return         Result of the operation
 */
ArrayResult array_size(Array* array, size_t* size_out);

/**
 * @brief Get the capacity of an array
 * 
 * @param array        Array to get the capacity of
 * @param capacity_out Output capacity
 * @return             Result of the operation
 */
ArrayResult array_capacity(Array* array, size_t* capacity_out);

/**
 * @brief Add an element to the array
 * 
 * @param array   Array to add the element to
 * @param element Element to add
 * @return        Result of the operation
 */
ArrayResult array_add(Array* array, void* element);

/**
 * @brief Remove an element from the array
 * 
 * @param array Array to remove the element from
 * @param index Index of the element to remove
 * @return      Result of the operation
 */
ArrayResult array_remove(Array* array, uint64_t index);

/**
 * @brief Get an element from the array
 * 
 * @param array       Array to get the element from
 * @param index       Index of the element to get
 * @param element_out Output element
 * @return            Result of the operation
 */
ArrayResult array_get(Array* array, uint64_t index, void* element_out);

/**
 * @brief Set an element in the array
 * 
 * @param array   Array to set the element in
 * @param index   Index of the element to set
 * @param element Element to set
 * @return        Result of the operation
 */
ArrayResult array_set(Array* array, uint64_t index, void* element);

/**
 * @brief Check if the array contains an element
 * 
 * @param array   Array to check
 * @param element Element to check for
 * @return        Result of the operation
 */
ArrayResult array_contains(Array* array, void* element);

/**
 * @brief Get the index of an element in the array
 * 
 * @param array     Array to get the index of
 * @param element   Element to get the index of
 * @param index_out Output index
 * @return          Result of the operation
 */
ArrayResult array_index_of(Array* array, void* element, uint64_t* index_out);

/**
 * @brief Destroy an array
 * 
 * @param array_ptr Pointer to the array to destroy
 * @return          Result of the operation
 */
ArrayResult array_destroy(Array** array_ptr);

#endif