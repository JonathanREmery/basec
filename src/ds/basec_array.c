#include "ds/basec_array.h"

static const u8 _GROWTH_FACTOR = 2;

/**
 * @brief Grow the array
 * @param array The array to grow
 * @return The result of the operation
 */
static BasecArrayResult _basec_array_grow(BasecArray* array) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;

    array->capacity *= _GROWTH_FACTOR;
    array->data = realloc(array->data, array->capacity * array->element_size);
    if (array->data == NULL) return BASEC_ARRAY_ALLOCATION_FAILURE;

    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Handle the result of an array operation
 * @param result The result of the operation
 */
void basec_array_handle_result(BasecArrayResult result) {
    switch (result) {
        case BASEC_ARRAY_SUCCESS:
            break;
        case BASEC_ARRAY_NULL_POINTER:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to a null pointer reference.\n"
            );
            exit(1);
        case BASEC_ARRAY_INVALID_ELEMENT_SIZE:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to an invalid element size.\n"
            );
            exit(1);
        case BASEC_ARRAY_INVALID_CAPACITY:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to an invalid capacity.\n"
            );
            exit(1);
        case BASEC_ARRAY_ALLOCATION_FAILURE:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to an allocation failure.\n"
            );
            exit(1);
        case BASEC_ARRAY_MEMOP_FAILURE:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to a memory operation failure.\n"
            );
            exit(1);
        case BASEC_ARRAY_EMPTY:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to an empty array.\n"
            );
            exit(1);
        case BASEC_ARRAY_OUT_OF_BOUNDS:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to an out of bounds index.\n"
            );
            exit(1);
        case BASEC_ARRAY_NOT_FOUND:
            (void)printf(
                "[Error][Array] "
                "Operation failed due to an element not being found.\n"
            );
            exit(1);
        default:
            (void)printf(
                "[Error][Array] "
                "An unknown error occurred during array operation.\n"
            );
            exit(1);
    }
}

/**
 * @brief Create an array
 * @param array The array to create
 * @param element_size The size of the elements in the array
 * @param capacity The capacity of the array
 */
BasecArrayResult basec_array_create(
    BasecArray** array, 
    u64          element_size, 
    u64          capacity
) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (element_size <= 0) return BASEC_ARRAY_INVALID_ELEMENT_SIZE;
    if (capacity <= 0) return BASEC_ARRAY_INVALID_CAPACITY;

    *array = (BasecArray*)malloc(sizeof(BasecArray));
    if (*array == NULL) return BASEC_ARRAY_ALLOCATION_FAILURE;

    (*array)->data = malloc(element_size * capacity);
    if ((*array)->data == NULL) return BASEC_ARRAY_ALLOCATION_FAILURE;

    (*array)->element_size = element_size;
    (*array)->length = 0;
    (*array)->capacity = capacity;

    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Append an element to the array
 * @param array The array to append to
 * @param element The element to append
 * @return The result of the operation
 */
BasecArrayResult basec_array_append(BasecArray* array, void* element) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (element == NULL) return BASEC_ARRAY_NULL_POINTER;

    BasecArrayResult result = BASEC_ARRAY_SUCCESS;

    if (array->length >= array->capacity) {
        result = _basec_array_grow(array);
        if (result != BASEC_ARRAY_SUCCESS) return result;
    }

    if (memcpy(
        (void*)((u64)array->data + array->length * array->element_size),
        element,
        array->element_size
    ) == NULL) return BASEC_ARRAY_MEMOP_FAILURE;

    array->length++;
    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Push an element to the array (same as append)
 * @param array The array to push to
 * @param element The element to push
 * @return The result of the operation
 */
BasecArrayResult basec_array_push(BasecArray* array, void* element) {
    if (array == NULL || element == NULL) return BASEC_ARRAY_NULL_POINTER;
    return basec_array_append(array, element);
}

/**
 * @brief Pop an element from the array
 * @param array The array to pop from
 * @param element_out The element to pop
 * @return The result of the operation
 */
BasecArrayResult basec_array_pop(BasecArray* array, void* element_out) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (element_out == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (array->length == 0) return BASEC_ARRAY_EMPTY;

    array->length--;

    if (memcpy(
        element_out,
        (void*)((u64)array->data + array->length * array->element_size),
        array->element_size
    ) == NULL) return BASEC_ARRAY_MEMOP_FAILURE;

    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Get an element from the array
 * @param array The array to get from
 * @param index The index of the element to get
 * @param element_out The element to get
 * @return The result of the operation
 */
BasecArrayResult basec_array_get(
    BasecArray* array,
    u64         index,
    void*       element_out
) {
    if (array == NULL || element_out == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (index >= array->length) return BASEC_ARRAY_OUT_OF_BOUNDS;

    if (memcpy(
        element_out,
        (void*)((u64)array->data + index * array->element_size),
        array->element_size
    ) == NULL) return BASEC_ARRAY_MEMOP_FAILURE;

    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Set an element in the array
 * @param array The array to set in
 * @param index The index of the element to set
 * @param element The element to set
 * @return The result of the operation
 */
BasecArrayResult basec_array_set(BasecArray* array, u64 index, void* element) {
    if (array == NULL || element == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (index >= array->length) return BASEC_ARRAY_OUT_OF_BOUNDS;

    if (memcpy(
        (void*)((u64)array->data + index * array->element_size),
        element,
        array->element_size
    ) == NULL) return BASEC_ARRAY_MEMOP_FAILURE;

    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Check if the array contains an element
 * @param array The array to check
 * @param element The element to check
 * @param contains_out The result of the operation
 * @return The result of the operation
 */
BasecArrayResult basec_array_contains(
    BasecArray* array,
    void*       element,
    bool*       contains_out
) {
    if (array == NULL || element == NULL || contains_out == NULL) {
        return BASEC_ARRAY_NULL_POINTER;
    }

    for (u64 i = 0; i < array->length; i++) {
        if (memcmp(
            (void*)((u64)array->data + i * array->element_size),
            element,
            array->element_size
        ) == 0) {
            *contains_out = true;
            return BASEC_ARRAY_SUCCESS;
        }
    }

    *contains_out = false;
    return BASEC_ARRAY_SUCCESS;
}

/** 
 * @brief Find the index of an element in the array
 * @param array The array to find from
 * @param element The element to find
 * @return The result of the operation
 */
BasecArrayResult basec_array_find(
    BasecArray* array,
    void*       element,
    u64*        index_out
) {
    if (array == NULL || element == NULL || index_out == NULL) {
        return BASEC_ARRAY_NULL_POINTER;
    }

    for (u64 i = 0; i < array->length; i++) {
        if (memcmp(
            (void*)((u64)array->data + i * array->element_size),
            element,
            array->element_size
        ) == 0) {
            *index_out = i;
            return BASEC_ARRAY_SUCCESS;
        }
    }

    *index_out = -1;
    return BASEC_ARRAY_NOT_FOUND;
}

/**
 * @brief Find all instances of an element in the array
 * @param array The array to find the element in
 * @param element The element to find
 * @param array_out The array to store the indices in
 * @return The result of the operation
 */
BasecArrayResult basec_array_find_all(
    BasecArray*  array,
    void*        element,
    BasecArray** array_out
) {
    if (array == NULL || element == NULL || array_out == NULL) {
        return BASEC_ARRAY_NULL_POINTER;
    }

    BasecArrayResult array_result;
    BasecArray*      indices;

    array_result = basec_array_create(
        &indices,
        sizeof(u64),
        2
    );
    if (array_result != BASEC_ARRAY_SUCCESS) return array_result;

    for (u64 i = 0; i < array->length; i++) {
        void* cur_element = NULL;
        array_result = basec_array_get(
            array,
            i,
            cur_element
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return array_result;

        if (memcmp(cur_element, element, array->element_size) == 0) {
            array_result = basec_array_append(
                indices,
                &i
            );
            if (array_result != BASEC_ARRAY_SUCCESS) return array_result;
        }
    }

    if (*array_out != NULL) {
        array_result = basec_array_destroy(array_out);
        if (array_result != BASEC_ARRAY_SUCCESS) return array_result;
    }

    *array_out = indices;
    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Destroy an array
 * @param array The array to destroy
 * @return The result of the operation
 */
BasecArrayResult basec_array_destroy(BasecArray** array) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;

    free((*array)->data);
    free(*array);
    *array = NULL;

    return BASEC_ARRAY_SUCCESS;
}
