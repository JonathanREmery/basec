#include "ds/basec_string.h"

// Growth factor for the string
static const u8 _GROWTH_FACTOR = 2;

/**
 * @brief Grow the string to a new capacity
 * @param string The string to grow
 * @param new_capacity The new capacity of the string
 * @return The result of the operation
 */
static BasecStringResult _basec_string_grow(BasecString* string, u64 new_capacity) {
    if (string == NULL || new_capacity <= 0) return BASEC_STRING_NULL_POINTER;

    string->data = (char*)realloc(string->data, new_capacity * _GROWTH_FACTOR);
    if (string->data == NULL) return BASEC_STRING_ALLOCATION_FAILURE;

    string->capacity = new_capacity;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Handle the result of a string operation by printing an appropriate error message.
 * @param result The result of the string operation to handle, indicating success or the type of error encountered.
 */
void basec_string_handle_result(BasecStringResult result) {
    switch (result) {
        case BASEC_STRING_SUCCESS:
            break;
        case BASEC_STRING_NULL_POINTER:
            (void)printf(
                "[Error][String] Operation failed due to a null pointer reference.\n"
            );
            exit(1);
        case BASEC_STRING_ALLOCATION_FAILURE:
            (void)printf(
                "[Error][String] Memory allocation failed while attempting to create or manipulate the string.\n"
            );
            exit(1);
        case BASEC_STRING_MEMOP_FAILURE:
            (void)printf(
                "[Error][String] A memory operation failed, indicating potential corruption or access issues.\n"
            );
            exit(1);
        case BASEC_STRING_ARRAY_FAILURE:
            (void)printf(
                "[Error][String] An array operation failed.\n"
            );
            exit(1);
        default:
            (void)printf(
                "[Error][String] An unknown error occurred during string operation.\n"
            );
            exit(1);
    }
}

/**
 * @brief Create a new string
 * @param string The string to create
 * @param str The c_str to create the string from
 * @param capacity The capacity of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_create(BasecString** string, const c_str str, u64 capacity) {
    if (str == NULL || capacity <= 0) return BASEC_STRING_NULL_POINTER;

    *string = (BasecString*)malloc(sizeof(BasecString));
    if (*string == NULL) return BASEC_STRING_ALLOCATION_FAILURE;

    (*string)->length = strlen(str);
    if ((*string)->length > capacity) capacity = (*string)->length * _GROWTH_FACTOR;

    (*string)->data = (c_str)malloc(capacity + 1);
    if ((*string)->data == NULL) return BASEC_STRING_ALLOCATION_FAILURE;

    if (strncpy(
        (*string)->data,
        str,
        (*string)->length
    ) == NULL) return BASEC_STRING_MEMOP_FAILURE;
    (*string)->data[(*string)->length] = '\0';

    (*string)->capacity = capacity;

    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Get the string as a c_str
 * @param string The string to get
 * @param str_out The c_str to store the string in
 * @return The result of the operation
 */
BasecStringResult basec_string_c_str(BasecString* string, c_str* str_out) {
    if (string == NULL || str_out == NULL) return BASEC_STRING_NULL_POINTER;

    *str_out = string->data;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Get the length of the string
 * @param string The string to get the length of
 * @param length_out The length of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_length(BasecString* string, u64* length_out) {
    if (string == NULL || length_out == NULL) return BASEC_STRING_NULL_POINTER;

    *length_out = string->length;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Get the capacity of the string
 * @param string The string to get the capacity of
 * @param capacity_out The capacity of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_capacity(BasecString* string, u64* capacity_out) {
    if (string == NULL || capacity_out == NULL) return BASEC_STRING_NULL_POINTER;

    *capacity_out = string->capacity;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend_str The string to prepend
 * @return The result of the operation
 */
BasecStringResult basec_string_prepend(BasecString* string, const c_str prepend_str) {
    if (string == NULL || prepend_str == NULL) return BASEC_STRING_NULL_POINTER;

    u64 prepend_len = strlen(prepend_str);
    u64 new_len = string->length + prepend_len;

    if (new_len > string->capacity) _basec_string_grow(string, new_len);
    
    if (memmove(
        string->data + prepend_len,
        string->data,
        string->length
    ) == NULL) return BASEC_STRING_MEMOP_FAILURE;

    if (memcpy(
        string->data,
        prepend_str,
        prepend_len
    ) == NULL) return BASEC_STRING_MEMOP_FAILURE;

    string->length = new_len;
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Append a string to the string
 * @param string The string to append to
 * @param append_str The string to append
 * @return The result of the operation
 */
BasecStringResult basec_string_append(BasecString* string, const c_str append_str) {
    if (string == NULL || append_str == NULL) return BASEC_STRING_NULL_POINTER;

    u64 append_len = strlen(append_str);
    u64 new_len = string->length + append_len;

    if (new_len > string->capacity) _basec_string_grow(string, new_len);

    if (strncpy(
        string->data + string->length,
        append_str,
        append_len
    ) == NULL) return BASEC_STRING_MEMOP_FAILURE;

    string->length = new_len;
    string->data[string->length] = '\0';

    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Find a substring in the string
 * @param string The string to find the substring in
 * @param substr The substring to find
 * @param index_out The index of the substring
 * @return The result of the operation
 */
BasecStringResult basec_string_find(BasecString* string, const c_str substr, u64* index_out) {
    if (string == NULL || substr == NULL || index_out == NULL) {
        return BASEC_STRING_NULL_POINTER;
    }

    char* substr_ptr = strstr(string->data, substr);
    if (substr_ptr == NULL) return BASEC_STRING_NOT_FOUND;

    *index_out = (u64)(substr_ptr - string->data);
    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Split a string into an array of strings
 * @param string The string to split
 * @param delimiter The delimiter to split the string by
 * @param array_out The array to store the split strings in
 * @return The result of the operation
 */
BasecStringResult basec_string_split(
    BasecString* string,
    const c_str delimiter,
    BasecArray** array_out
) {
    if (string == NULL || delimiter == NULL || array_out == NULL) {
        return BASEC_STRING_NULL_POINTER;
    }

    BasecArray*       substr_indices;
    BasecArrayResult  array_result;
    BasecString*      substring;
    BasecStringResult string_result;
    u64               substr_start;
    u64               substr_end;
    u64               delim_len;

    if (*array_out == NULL) { 
        array_result = basec_array_create(
            array_out,
            sizeof(BasecString*),
            2
        );

        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;
    }

    array_result = basec_array_create(
        &substr_indices,
        sizeof(u64),
        2
    );
    if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;

    substr_start = 0;
    substr_end   = string->length;
    delim_len    = strlen(delimiter);

    if (delim_len < string->length) {
        for (u64 i = 0; i < string->length - delim_len; i++) {
            if (strncmp(
                string->data + i,
                delimiter,
                delim_len
            ) == 0) {
                substr_end = i;

                array_result = basec_array_push(
                    substr_indices,
                    &substr_start
                );
                if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;

                array_result = basec_array_push(
                    substr_indices,
                    &substr_end
                );
                if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;

                substr_start = i + delim_len;
            }
        }
    }

    if (substr_indices->length == 0) {
        array_result = basec_array_push(
            substr_indices,
            &substr_start
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;

        substr_end = string->length;
        array_result = basec_array_push(
            substr_indices,
            &substr_end
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;
    } else {
        substr_start = substr_end + delim_len;
        array_result = basec_array_push(
            substr_indices,
            &substr_start
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;
        
        substr_end = string->length;
        array_result = basec_array_push(
            substr_indices,
            &substr_end
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;
    }

    for (u64 i = 0; i < substr_indices->length; i += 2) {
        array_result = basec_array_get(
            substr_indices,
            i,
            &substr_start
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;

        array_result = basec_array_get(
            substr_indices,
            i + 1,
            &substr_end
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;

        c_str substr = string->data + substr_start;
        substr[substr_end - substr_start] = '\0';

        string_result = basec_string_create(
            &substring,
            substr,
            substr_end - substr_start
        );
        if (string_result != BASEC_STRING_SUCCESS) return string_result;

        array_result = basec_array_push(
            *array_out,
            &substring
        );
        if (array_result != BASEC_ARRAY_SUCCESS) return BASEC_STRING_ARRAY_FAILURE;
    }

    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Destroy a string
 * @param string The string to destroy
 */
BasecStringResult basec_string_destroy(BasecString** string) {
    if (*string == NULL) return BASEC_STRING_NULL_POINTER;

    free((*string)->data);
    free(*string);
    *string = NULL;

    return BASEC_STRING_SUCCESS;
}

/**
 * @brief Destroy an array of strings
 * @param string_arr The array of strings to destroy
 * @return The result of the operation
 */
BasecStringResult basec_strings_destroy(BasecArray** string_arr) {
    if (*string_arr == NULL) return BASEC_STRING_NULL_POINTER;

    for (u64 i = 0; i < (*string_arr)->length; i++) {
        BasecString* substr;
        basec_array_get(*string_arr, i, &substr);
        basec_string_destroy(&substr);
    }

    basec_array_destroy(string_arr);
    return BASEC_STRING_SUCCESS;
}
