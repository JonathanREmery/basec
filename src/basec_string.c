/**
 * @file string.c
 * @brief A simple string implementation
 */
#include "basec_string.h"

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
        case STRING_ERROR_MALLOC:
            return "STRING_ERROR_MALLOC";
        case STRING_ERROR_REALLOC:
            return "STRING_ERROR_REALLOC";
        case STRING_ERROR_EMPTY:
            return "STRING_ERROR_EMPTY";
        default:
            return "UNKNOWN_STRING_RESULT";
    }
}

/**
 * @brief Create a new string
 * 
 * @param str The string to create
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_create(const char* str, String** str_out) {
    // Check for NULL pointers
    if (str == NULL || str_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Allocate memory for the string
    String* string = (String*)malloc(sizeof(String));
    if (string == NULL) {
        return STRING_ERROR_MALLOC;
    }

    // Allocate memory for the string data
    string->data = (char*)malloc(strlen(str) + 1);
    if (string->data == NULL) {
        free(string);
        return STRING_ERROR_MALLOC;
    }

    // Get the length of the string
    string->length = strlen(str);

    // Copy the string data and null-terminate it
    memcpy(string->data, str, string->length);
    string->data[string->length] = '\0';

    // Set the output string
    *str_out = string;

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

    // Set the length of the string
    size_t new_length = strlen(value);

    // Reallocate memory for the string
    char* new_data = (char*)realloc(str->data, new_length + 1);
    if (new_data == NULL) {
        return STRING_ERROR_REALLOC;
    }

    // Set the new data and length
    str->data = new_data;
    str->length = new_length;

    // Copy the value to the string and null-terminate it
    memcpy(str->data, value, str->length);
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
        return STRING_ERROR_MALLOC;
    }

    // Set the length of the copied string
    (*str_out)->length = str->length;

    // Copy the string data and null-terminate it
    memcpy((*str_out)->data, str->data, str->length);
    (*str_out)->data[str->length] = '\0';

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

    // Allocate memory for the concatenated string structure
    String* concat_str = (String*)malloc(sizeof(String));
    if (concat_str == NULL) {
        return STRING_ERROR_MALLOC;
    }

    // Allocate memory for the concatenated string data
    concat_str->data = (char*)malloc(str1->length + str2->length + 1);
    if (concat_str->data == NULL) {
        free(concat_str);
        return STRING_ERROR_MALLOC;
    }

    // Copy the strings and null-terminate the concatenated string
    memcpy(concat_str->data, str1->data, str1->length);
    memcpy(concat_str->data + str1->length, str2->data, str2->length);
    concat_str->data[str1->length + str2->length] = '\0';

    // Set the length of the concatenated string
    concat_str->length = str1->length + str2->length;

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
        return STRING_ERROR_EMPTY;
    }

    // Check if the substring is contained in the string
    *contains_out = strstr(str->data, substr->data) != NULL;

    // Return the success result
    return STRING_SUCCESS;
}

/**
 * @brief Destroy a string
 * 
 * @param str The string to destroy
 * @return A StringResult
 */
StringResult string_destroy(String* str) {
    // Check if the string is NULL
    if (str == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Free the string data and structure
    free(str->data);
    free(str);

    // Return the success result
    return STRING_SUCCESS;
}