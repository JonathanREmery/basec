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
    // Check if the string is NULL
    if (str == NULL || str_out == NULL) {
        return STRING_ERROR_NULL_POINTER;
    }

    // Allocate memory for the string
    String* string = (String*)malloc(sizeof(String));

    // Check if the memory allocation failed
    if (string == NULL) {
        return STRING_ERROR_MALLOC;
    }

    // Allocate memory for the string data
    string->data = (char*)malloc(strlen(str) + 1);

    // Check if the memory allocation failed
    if (string->data == NULL) {
        free(string);
        return STRING_ERROR_MALLOC;
    }

    // Copy the string data and set the length
    strcpy(string->data, str);
    string->length = strlen(str);

    // Set the output string
    *str_out = string;

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
    // Check if the string is NULL
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

    // Create a new string
    StringResult result = string_create(str->data, str_out);

    // Return the result
    return result;
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
    // Check if the strings are NULL
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

    // Copy the strings
    memcpy(concat_str->data, str1->data, str1->length);
    memcpy(concat_str->data + str1->length, str2->data, str2->length);

    // Null-terminate the concatenated string
    concat_str->data[str1->length + str2->length] = '\0';

    // Set the length of the concatenated string
    concat_str->length = str1->length + str2->length;

    // Set the output string
    *str_out = concat_str;

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