#include "ds/basec_string.h"

// Growth factor for the string
static const u8 _GROWTH_FACTOR = 2;

/**
 * @brief Create a new string
 * @param string The string to create
 * @param str The c_str to create the string from
 * @param capacity The capacity of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_create(BasecString** string, const c_str str, u64 capacity) {
    if (str == NULL || capacity <= 0) return BASEC_STRING_FAILURE;

    *string = (BasecString*)malloc(sizeof(BasecString));
    if (*string == NULL) return BASEC_STRING_FAILURE;

    (*string)->length = strlen(str);
    if ((*string)->length > capacity) capacity = (*string)->length * _GROWTH_FACTOR;

    (*string)->data = (c_str)malloc(capacity + 1);
    if ((*string)->data == NULL) return BASEC_STRING_FAILURE;

    (void)strncpy((*string)->data, str, (*string)->length);
    (*string)->data[(*string)->length + 1] = '\0';

    (*string)->capacity = capacity;

    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Get the string as a c_str
 * @param string The string to get
 * @param str_out The c_str to store the string in
 * @return The result of the operation
 */
BasecStringResult basec_string_c_str(BasecString** string, c_str* str_out) {
    if (*string == NULL || str_out == NULL) return BASEC_STRING_FAILURE;

    *str_out = (*string)->data;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Get the length of the string
 * @param string The string to get the length of
 * @param length_out The length of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_length(BasecString** string, u64* length_out) {
    if (*string == NULL || length_out == NULL) return BASEC_STRING_FAILURE;

    *length_out = (*string)->length;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Get the capacity of the string
 * @param string The string to get the capacity of
 * @param capacity_out The capacity of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_capacity(BasecString** string, u64* capacity_out) {
    if (*string == NULL || capacity_out == NULL) return BASEC_STRING_FAILURE;

    *capacity_out = (*string)->capacity;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend_str The string to prepend
 * @return The result of the operation
 */
static BasecStringResult _basec_string_grow(BasecString** string, u64 new_capacity) {
    if (*string == NULL || new_capacity <= 0) return BASEC_STRING_FAILURE;

    (*string)->data = (char*)realloc((*string)->data, new_capacity * _GROWTH_FACTOR);
    if ((*string)->data == NULL) return BASEC_STRING_FAILURE;

    (*string)->capacity = new_capacity;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend_str The string to prepend
 * @return The result of the operation
 */
BasecStringResult basec_string_prepend(BasecString** string, const c_str prepend_str) {
    if (*string == NULL || prepend_str == NULL) return BASEC_STRING_FAILURE;

    u64 prepend_len = strlen(prepend_str);
    u64 new_len = (*string)->length + prepend_len;

    if (new_len > (*string)->capacity) _basec_string_grow(string, new_len);
    
    (void)memmove((*string)->data + prepend_len, (*string)->data, (*string)->length);
    (void)memcpy((*string)->data, prepend_str, prepend_len);

    (*string)->length = new_len;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Append a string to the string
 * @param string The string to append to
 * @param append_str The string to append
 * @return The result of the operation
 */
BasecStringResult basec_string_append(BasecString** string, const c_str append_str) {
    if (*string == NULL || append_str == NULL) return BASEC_STRING_FAILURE;

    u64 append_len = strlen(append_str);
    u64 new_len = (*string)->length + append_len;

    if (new_len > (*string)->capacity) _basec_string_grow(string, new_len);

    (void)strncpy((*string)->data + (*string)->length, append_str, append_len);
    (*string)->length = new_len;
    (*string)->data[(*string)->length + 1] = '\0';

    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Destroy a string
 * @param string The string to destroy
 */
BasecStringResult basec_string_destroy(BasecString** string) {
    if (*string == NULL) return BASEC_STRING_FAILURE;

    free((*string)->data);
    free(*string);
    *string = NULL;

    return BASEC_STRING_SUCCESS;
}