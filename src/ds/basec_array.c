/**
 * @file basec_array.c
 * @brief Implementation of an Array type and functions
 */

#include "ds/basec_array.h"

/**
 * @brief Convert an ArrayResult to a string
 * 
 * @param result ArrayResult to convert
 * @return       String representation of the ArrayResult
 */
const char* array_result_to_string(ArrayResult result) {
    // Switch on the result
    switch (result) {
        case ARRAY_SUCCESS:
            return "ARRAY_SUCCESS";                    //< Success
        case ARRAY_ERROR_NULL_POINTER:
            return "ARRAY_ERROR_NULL_POINTER";         //< NULL pointer
        case ARRAY_ERROR_INVALID_CAPACITY:
            return "ARRAY_ERROR_INVALID_CAPACITY";     //< Invalid capacity
        case ARRAY_ERROR_INVALID_ELEMENT_SIZE:
            return "ARRAY_ERROR_INVALID_ELEMENT_SIZE"; //< Invalid element size
        case ARRAY_ERROR_MALLOC:
            return "ARRAY_ERROR_MALLOC";               //< Malloc failed
        case ARRAY_ERROR_REALLOC:
            return "ARRAY_ERROR_REALLOC";              //< Realloc failed
        case ARRAY_ERROR_MEMCPY:
            return "ARRAY_ERROR_MEMCPY";               //< Memcpy failed
        case ARRAY_ERROR_MEMMOVE:
            return "ARRAY_ERROR_MEMMOVE";              //< Memmove failed
        case ARRAY_ERROR_OUT_OF_BOUNDS:
            return "ARRAY_ERROR_OUT_OF_BOUNDS";        //< Out of bounds
        case ARRAY_ERROR_EMPTY:
            return "ARRAY_ERROR_EMPTY";                //< Empty
        case ARRAY_FOUND:
            return "ARRAY_FOUND";                      //< Found
        case ARRAY_ERROR_NOT_FOUND:
            return "ARRAY_ERROR_NOT_FOUND";            //< Not found
        default:
            return "UNKNOWN_ARRAY_RESULT";             //< Unknown result
    }
}

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
) {
    // Check validity of element size, capacity, and array output
    if (element_size < 1) return ARRAY_ERROR_INVALID_ELEMENT_SIZE;
    if (capacity < 1) return ARRAY_ERROR_INVALID_CAPACITY;
    if (array_out == NULL) return ARRAY_ERROR_NULL_POINTER;

    // Allocate memory for the array
    Array* array = (Array*)malloc(sizeof(Array));

    // Check if the allocation failed
    if (array == NULL) return ARRAY_ERROR_MALLOC;

    // Set the array size, element size, and capacity
    array->size = 0;
    array->element_size = element_size;
    array->capacity = capacity;

    // Allocate memory for the data
    array->data = malloc(element_size * capacity);

    // Check if the allocation failed
    if (array->data == NULL) {
        // Free the array
        free(array);
        array = NULL;

        // Malloc failed
        return ARRAY_ERROR_MALLOC;
    }

    // Set the output array
    *array_out = array;

    // Success
    return ARRAY_SUCCESS;
}

/**
 * @brief Resize the capacity of an array
 * 
 * @param array        Array to resize
 * @param new_capacity New capacity
 * @return             Result of the operation
 */
ArrayResult array_resize(Array* array, size_t new_capacity) {
    // Check validity of array and new capacity
    if (array == NULL) return ARRAY_ERROR_NULL_POINTER;
    if (new_capacity < 1) return ARRAY_ERROR_INVALID_CAPACITY;
    
    // Check if capacity is already large enough
    if (new_capacity <= array->capacity) {
        // Update the capacity
        array->capacity = new_capacity;

        // Success
        return ARRAY_SUCCESS;
    }

    // Reallocate memory for the array
    array->data = (void*)realloc(
        array->data,
        new_capacity * array->element_size
    );

    // Check if the reallocation failed
    if (array->data == NULL) return ARRAY_ERROR_REALLOC;

    // Update the capacity
    array->capacity = new_capacity;

    // Success
    return ARRAY_SUCCESS;
}

/**
 * @brief Get the size of an array
 * 
 * @param array    Array to get the size of
 * @param size_out Output size
 * @return         Result of the operation
 */
ArrayResult array_size(Array* array, size_t* size_out) {
    // Check for NULL pointers
    if (array == NULL || size_out == NULL) return ARRAY_ERROR_NULL_POINTER;

    // Set the output size
    *size_out = array->size;

    // Success
    return ARRAY_SUCCESS;
}

/**
 * @brief Get the capacity of an array
 * 
 * @param array        Array to get the capacity of
 * @param capacity_out Output capacity
 * @return             Result of the operation
 */
ArrayResult array_capacity(Array* array, size_t* capacity_out) {
    // Check for NULL pointers
    if (array == NULL || capacity_out == NULL) return ARRAY_ERROR_NULL_POINTER;

    // Set the output capacity
    *capacity_out = array->capacity;

    // Success
    return ARRAY_SUCCESS;
}

/**
 * @brief Add an element to the array
 * 
 * @param array   Array to add the element to
 * @param element Element to add
 * @return        Result of the operation
 */
ArrayResult array_add(Array* array, void* element) {
    // Check for NULL pointers
    if (array == NULL || element == NULL) return ARRAY_ERROR_NULL_POINTER;

    // Check if the array is full
    if (array->size >= array->capacity) {
        // Resize the array to double the capacity
        ArrayResult resize_result = array_resize(array, array->capacity * 2);

        // Check if the resize failed
        if (resize_result != ARRAY_SUCCESS) {
            // Resize failed
            return resize_result;
        }
    }

    // Copy the element to the array
    void* memcpy_result = memcpy(
        array->data + array->element_size * array->size,
        element,
        array->element_size
    );

    // Check if the copy failed
    if (memcpy_result == NULL) return ARRAY_ERROR_MEMCPY;

    // Increment the size of the array
    array->size++;

    // Success
    return ARRAY_SUCCESS;
}

/**
 * @brief Remove an element from the array
 * 
 * @param array Array to remove the element from
 * @param index Index of the element to remove
 * @return      Result of the operation
 */
ArrayResult array_remove(Array* array, uint64_t index) {
    // Check the validity of the array and index
    if (array == NULL) return ARRAY_ERROR_NULL_POINTER;
    if (index >= array->size) return ARRAY_ERROR_OUT_OF_BOUNDS;

    // Get the destination and source pointers
    void* dest = array->data + index * array->element_size;
    void* src = dest + array->element_size;

    // Calculate the number of bytes to shift
    size_t num_bytes = (array->size - index - 1) * array->element_size;

    // Check if there is data to shift
    if (num_bytes > 0) {
        // Shift the data left
        void* shifted_data = memmove(dest, src, num_bytes);

        // Check if the shift was successful
        if (shifted_data == NULL) {
            // Memmove failed
            return ARRAY_ERROR_MEMMOVE;
        }
    }

    // Decrement the size of the array
    array->size--;

    // Success
    return ARRAY_SUCCESS;
}

/**
 * @brief Get an element from the array
 * 
 * @param array       Array to get the element from
 * @param index       Index of the element to get
 * @param element_out Output element
 * @return            Result of the operation
 */
ArrayResult array_get(Array* array, uint64_t index, void* element_out) {
    // Check for validity of array, index, and element output
    if (array == NULL || element_out == NULL) return ARRAY_ERROR_NULL_POINTER;
    if (index >= array->size) return ARRAY_ERROR_OUT_OF_BOUNDS;

    // Copy the element from the array
    void* memcpy_result = memcpy(
        element_out,
        array->data + index * array->element_size,
        array->element_size
    );

    // Check if the copy failed
    if (memcpy_result == NULL) return ARRAY_ERROR_MEMCPY;

    // Success
    return ARRAY_SUCCESS;
}

/**
 * @brief Set an element in the array
 * 
 * @param array   Array to set the element in
 * @param index   Index of the element to set
 * @param element Element to set
 * @return        Result of the operation
 */
ArrayResult array_set(Array* array, uint64_t index, void* element) {
    // Check the validity of the array, index, and element
    if (array == NULL || element == NULL) return ARRAY_ERROR_NULL_POINTER;
    if (index >= array->size) return ARRAY_ERROR_OUT_OF_BOUNDS;

    // Copy the element to the array
    void* memcpy_result = memcpy(
        array->data + index * array->element_size,
        element,
        array->element_size
    );

    // Check if the copy failed
    if (memcpy_result == NULL) return ARRAY_ERROR_MEMCPY;

    // Success
    return ARRAY_SUCCESS;
}   

/**
 * @brief Check if the array contains an element
 * 
 * @param array   Array to check
 * @param element Element to check for
 * @return        Result of the operation
 */
ArrayResult array_contains(Array* array, void* element) {
    // Check for NULL pointers
    if (array == NULL || element == NULL) return ARRAY_ERROR_NULL_POINTER;

    // Iterate over the array elements
    for (uint64_t i = 0; i < array->size; i++) {
        // Get the current element
        void* current_element = array->data + i * array->element_size;

        // Check if the elements match
        if (memcmp(current_element, element, array->element_size) == 0) {
            // Found
            return ARRAY_FOUND;
        }
    }

    // Not found
    return ARRAY_ERROR_NOT_FOUND;
}

/**
 * @brief Get the index of an element in the array
 * 
 * @param array     Array to get the index of
 * @param element   Element to get the index of
 * @param index_out Output index
 * @return          Result of the operation
 */
ArrayResult array_index_of(Array* array, void* element, uint64_t* index_out) {
    // Check for NULL pointers
    if (array == NULL || element == NULL || index_out == NULL) {
        // NULL pointer
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Check if the array is empty
    if (array->size == 0) return ARRAY_ERROR_EMPTY;

    // Iterate over the array elements
    for (uint64_t i = 0; i < array->size; i++) {
        // Get the current element
        void* current_element = array->data + i * array->element_size;

        // Check if the elements match
        if (memcmp(current_element, element, array->element_size) == 0) {
            // Set the output index
            *index_out = i;

            // Found
            return ARRAY_FOUND;
        }
    }

    // Not found
    return ARRAY_ERROR_NOT_FOUND;
}

/**
 * @brief Destroy an array
 * 
 * @param array_ptr Pointer to the array to destroy
 * @return          Result of the operation
 */
ArrayResult array_destroy(Array** array_ptr) {
    // Check for NULL pointers
    if (array_ptr == NULL || *array_ptr == NULL) {
        // NULL pointer
        return ARRAY_ERROR_NULL_POINTER;
    }

    // Free the array data
    free((*array_ptr)->data);
    (*array_ptr)->data = NULL;

    // Free the array structure
    free(*array_ptr);
    *array_ptr = NULL;

    // Success
    return ARRAY_SUCCESS;
}