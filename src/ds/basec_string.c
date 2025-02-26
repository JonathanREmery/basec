/**
 * @file basec_string.c
 * @brief Implementation of a String type and functions
 */

#include "ds/basec_string.h"

/**
 * @brief Convert a StringResult to a string
 * 
 * @param result The StringResult to convert
 * @return A string representation of the StringResult
 */
const char* string_result_to_string(StringResult result) {
    switch (result) {
        case STRING_SUCCESS:
            return "STRING_SUCCESS";
        case STRING_ERROR_NULL_POINTER:
            return "STRING_ERROR_NULL_POINTER";
        case STRING_ERROR_INVALID_CAPACITY:
            return "STRING_ERROR_INVALID_CAPACITY";
        case STRING_ERROR_CAPACITY_TOO_SMALL:
            return "STRING_ERROR_CAPACITY_TOO_SMALL";
        case STRING_ERROR_MALLOC:
            return "STRING_ERROR_MALLOC";
        case STRING_ERROR_REALLOC:
            return "STRING_ERROR_REALLOC";
        case STRING_ERROR_MEMCPY:
            return "STRING_ERROR_MEMCPY";
        case STRING_ERROR_EMPTY:
            return "STRING_ERROR_EMPTY";
        case STRING_ERROR_NOT_FOUND:
            return "STRING_ERROR_NOT_FOUND";
        default:
            return "UNKNOWN_STRING_RESULT";
    }
}

/**
 * @brief Create a new string
 * 
 * @param str The string to create
 * @param capacity The capacity of the string
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_create(const char* str, size_t capacity, String** str_out) {
    // Check for NULL pointers
    if (str == NULL || str_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if the capacity is valid
    if (capacity < 1) {
        return STRING_ERROR_INVALID_CAPACITY;
    }

    // Allocate memory for the string
    String* string = (String*)malloc(sizeof(String));
    if (string == NULL) {
        return STRING_ERROR_MALLOC;
    }

    // Allocate memory for the string data
    string->data = (char*)malloc(capacity + 1);
    if (string->data == NULL) {
        free(string);
        string = NULL;

        return STRING_ERROR_MALLOC;
    }

    // Get the length of the string
    string->length = strlen(str);

    // Check if the length exceeds the capacity
    if (string->length >= capacity) {
        free(string);
        string = NULL;

        return STRING_ERROR_CAPACITY_TOO_SMALL;
    }

    // Copy the string data
    void* memcpy_result = memcpy(string->data, str, string->length);
    if (memcpy_result == NULL) {
        free(string);
        string = NULL;

        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    string->data[string->length] = '\0';

    // Set the output string
    *str_out = string;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Resize the capacity of a string
 * 
 * @param str The string to resize
 * @param new_capacity The new capacity
 * @return A StringResult
 */
StringResult string_resize(String* str, size_t new_capacity) {
    // Check for NULL pointers
    if (str == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }
    
    // Check if the new capacity is valid
    if (new_capacity < 1 || new_capacity < str->length) {
        return STRING_ERROR_INVALID_CAPACITY;
    }
    
    // Check if the capacity is already large enough
    if (new_capacity <= str->capacity) {
        str->capacity = new_capacity;
        return STRING_SUCCESS;
    }

    // Reallocate memory for the string
    str->data = (char*)realloc(str->data, new_capacity + 1);
    if (str->data == NULL) {
        return STRING_ERROR_REALLOC;
    }

    // Update the capacity of the string
    str->capacity = new_capacity;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Set the value of a string
 * 
 * @param str The string to set
 * @param value The value to set the string to
 * @return A StringResult
 */
StringResult string_set(String* str, const char* value) {
    // Check for NULL pointers
    if (str == NULL || value == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if the strings are the same
    if (strcmp(str->data, value) == 0) {
        return STRING_SUCCESS;
    }

    // Calculate the new length of the string
    size_t new_length = strlen(value);

    // Check if string needs to be grown
    if (new_length >= str->capacity) {
        // Resize the string to double the new length
        StringResult resize_result = string_resize(str, new_length * 2);
        if (resize_result != STRING_SUCCESS) {
            return resize_result;
        }
    }

    // Set the length of the string
    str->length = new_length;

    // Copy the value to the string
    void* memcpy_result = memcpy(str->data, value, str->length);
    if (memcpy_result == NULL) {
        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    str->data[str->length] = '\0';

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Get the length of a string
 * 
 * @param str The string to get the length of
 * @param length_out The output length
 * @return A StringResult
 */
StringResult string_length(const String* str, size_t* length_out) {
    // Check for NULL pointers
    if (str == NULL || length_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Set the output length
    *length_out = str->length;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Get the capacity of a string
 * 
 * @param str The string to get the capacity of
 * @param capacity_out The output capacity
 * @return A StringResult
 */
StringResult string_capacity(const String* str, size_t* capacity_out) {
    // Check for NULL pointers
    if (str == NULL || capacity_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Set the output capacity
    *capacity_out = str->capacity;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Copy a string
 * 
 * @param str The string to copy
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_copy(String* str, String** str_out) {
    // Check if the string is NULL
    if (str == NULL || str_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Allocate memory for the string structure
    *str_out = (String*)malloc(sizeof(String));
    if (*str_out == NULL) {
        return STRING_ERROR_MALLOC;
    }

    // Allocate memory for the string data
    (*str_out)->data = (char*)malloc(str->length + 1);
    if ((*str_out)->data == NULL) {
        free(*str_out);
        *str_out = NULL;

        return STRING_ERROR_MALLOC;
    }

    // Set the length and capacity of the copied string
    (*str_out)->length = str->length;
    (*str_out)->capacity = str->capacity;

    // Copy the string data
    void* memcpy_result = memcpy((*str_out)->data, str->data, str->length);
    if (memcpy_result == NULL) {
        free(*str_out);
        *str_out = NULL;

        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    (*str_out)->data[str->length] = '\0';

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Append a string to another string
 * 
 * @param str The string to append to
 * @param substr The string to append
 * @return A StringResult
 */
StringResult string_append(String* str, String* substr) {
    // Check for NULL pointers
    if (str == NULL || substr == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if the substr is empty
    if (substr->length == 0) {
        return STRING_SUCCESS;
    }

    // Calculate the new length of the string
    size_t new_length = str->length + substr->length;

    // Check if the string needs to be grown
    if (new_length >= str->capacity) {
        // Resize the string to double the new length
        StringResult resize_result = string_resize(str, new_length * 2);
        if (resize_result != STRING_SUCCESS) {
            return resize_result;
        }
    }

    // Set the length of the string
    str->length = new_length;

    // Copy the substr to the end of the string
    void* memcpy_result = memcpy(str->data + str->length - substr->length, substr->data, substr->length);
    if (memcpy_result == NULL) {
        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    str->data[str->length] = '\0';

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Concatenate two strings
 * 
 * @param str1 The first string
 * @param str2 The second string
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_concat(String* str1, String* str2, String** str_out) {
    // Check for NULL pointers
    if (str1 == NULL || str2 == NULL || str_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if str1 is empty
    if (str1->length == 0) {
        // Copy str2 to str_out
        return string_copy(str2, str_out);
    }

    // Check if str2 is empty
    if (str2->length == 0) {
        // Copy str1 to str_out
        return string_copy(str1, str_out);
    }

    // Allocate memory for the concatenated string structure
    String* concat_str = (String*)malloc(sizeof(String));
    if (concat_str == NULL) {
        return STRING_ERROR_MALLOC;
    }

    // Calculate total length and capacity
    size_t total_length = str1->length + str2->length;
    size_t total_capacity = total_length * 2;

    // Allocate memory for the concatenated string data
    concat_str->data = (char*)malloc(total_capacity);
    if (concat_str->data == NULL) {
        free(concat_str);
        concat_str = NULL;

        return STRING_ERROR_MALLOC;
    }

    // Copy the first string
    void* memcpy_result = memcpy(concat_str->data, str1->data, str1->length);
    if (memcpy_result == NULL) {
        free(concat_str);
        concat_str = NULL;

        return STRING_ERROR_MEMCPY;
    }

    // Copy the second string
    memcpy_result = memcpy(concat_str->data + str1->length, str2->data, str2->length);
    if (memcpy_result == NULL) {
        free(concat_str);
        concat_str = NULL;

        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    concat_str->data[total_length] = '\0';

    // Set the length and capacity of the concatenated string
    concat_str->length = total_length;
    concat_str->capacity = total_capacity;

    // Set the output string
    *str_out = concat_str;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Check if a string contains another string
 * 
 * @param str The string to check
 * @param substr The substring to check for
 * @param contains_out The output contains
 * @return A StringResult
 */
StringResult string_contains(String* str, String* substr, bool* contains_out) {
    // Check for NULL pointers
    if (str == NULL || substr == NULL || contains_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if the substring is empty
    if (substr->length == 0) {
        *contains_out = true;
        return STRING_ERROR_EMPTY;
    }

    // Check if the substring is contained in the string
    char* strstr_result = strstr(str->data, substr->data);
    if (strstr_result == NULL) {
        *contains_out = false;
        return STRING_ERROR_NOT_FOUND;
    }

    // Set the output contains
    *contains_out = true;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Get the index of a substring in a string
 * 
 * @param str The string to check
 * @param substr The substring to check for
 * @param index_out The output index
 * @return A StringResult
 */
StringResult string_index_of(String* str, String* substr, size_t* index_out) {
    // Check for NULL pointers
    if (str == NULL || substr == NULL || index_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if the substring is empty
    if (substr->length == 0) {
        return STRING_ERROR_EMPTY;
    }

    // Check if the substring is contained in the string
    char* strstr_result = strstr(str->data, substr->data);
    if (strstr_result == NULL) {
        return STRING_ERROR_NOT_FOUND;
    }

    // Set the output index
    *index_out = strstr_result - str->data;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Destroy a string
 * 
 * @param str_ptr A pointer to the string to destroy
 * @return A StringResult
 */
StringResult string_destroy(String** str_ptr) {
    // Check if the string is NULL
    if (str_ptr == NULL || *str_ptr == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Free the string data
    free((*str_ptr)->data);
    (*str_ptr)->data = NULL;

    // Free the string structure
    free(*str_ptr);
    *str_ptr = NULL;

    // Return the success result
    return STRING_SUCCESS;
}