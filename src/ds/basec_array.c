#include "ds/basec_array.h"

static const u8 _GROWTH_FACTOR = 2;

/**
 * @brief Grow the array
 * @param array The array to grow
 * @return The result of the operation
 */
static ArrayResult _basec_array_grow(Array* array) {
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
void basec_array_handle_result(ArrayResult result) {
    switch (result) {
        case BASEC_ARRAY_SUCCESS:
            break;
        case BASEC_ARRAY_NULL_POINTER:
            (void)printf(
                "[Error][Array] Operation failed due to a null pointer reference.\n"
            );
            exit(1);
        case BASEC_ARRAY_INVALID_ELEMENT_SIZE:
            (void)printf(
                "[Error][Array] Operation failed due to an invalid element size.\n"
            );
            exit(1);
        case BASEC_ARRAY_INVALID_CAPACITY:
            (void)printf(
                "[Error][Array] Operation failed due to an invalid capacity.\n"
            );
            exit(1);
        case BASEC_ARRAY_ALLOCATION_FAILURE:
            (void)printf(
                "[Error][Array] Operation failed due to an allocation failure.\n"
            );
            exit(1);
        default:
            (void)printf(
                "[Error][Array] An unknown error occurred during array operation.\n"
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
ArrayResult basec_array_create(Array** array, u64 element_size, u64 capacity) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (element_size <= 0) return BASEC_ARRAY_INVALID_ELEMENT_SIZE;
    if (capacity <= 0) return BASEC_ARRAY_INVALID_CAPACITY;

    *array = (Array*)malloc(sizeof(Array));
    if (*array == NULL) return BASEC_ARRAY_ALLOCATION_FAILURE;

    (*array)->data = malloc(element_size * capacity);
    if ((*array)->data == NULL) return BASEC_ARRAY_ALLOCATION_FAILURE;

    (*array)->element_size = element_size;
    (*array)->length = 0;
    (*array)->capacity = capacity;

    return BASEC_ARRAY_SUCCESS;
}

/**
 * @brief Push an element to the array
 * @param array The array to push to
 * @param element The element to push
 * @return The result of the operation
 */
ArrayResult basec_array_push(Array* array, void* element) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;
    if (element == NULL) return BASEC_ARRAY_NULL_POINTER;

    if (array->length >= array->capacity) {
        ArrayResult result = _basec_array_grow(array);
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
 * @brief Pop an element from the array
 * @param array The array to pop from
 * @param element_out The element to pop
 * @return The result of the operation
 */
ArrayResult basec_array_pop(Array* array, void* element_out) {
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
 * @brief Destroy an array
 * @param array The array to destroy
 * @return The result of the operation
 */
ArrayResult basec_array_destroy(Array** array) {
    if (array == NULL) return BASEC_ARRAY_NULL_POINTER;

    free((*array)->data);
    free(*array);
    *array = NULL;

    return BASEC_ARRAY_SUCCESS;
}