/**
 * @file string.h
 * @brief A simple string implementation
 */
#ifndef BASEC_STRING_H
#define BASEC_STRING_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    STRING_SUCCESS,
    STRING_ERROR_NULL_POINTER,
    STRING_ERROR_MALLOC
} StringResult;

/**
 * @brief A simple string implementation
 */
typedef struct {
    char* data;
    size_t length;
} String;

/**
 * @brief Convert a StringResult to a string
 * 
 * @param result The StringResult to convert
 * @return A string representation of the StringResult
 */
const char* string_result_to_string(StringResult result);

/**
 * @brief Create a new string
 * 
 * @param str The string to create
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_create(const char* str, String** str_out);

/**
 * @brief Get the length of a string
 * 
 * @param str The string to get the length of
 * @return The length of the string
 */
StringResult string_length(const String* str, size_t* length_out);

/**
 * @brief Copy a string
 * 
 * @param str The string to copy
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_copy(String* str, String** str_out);

/**
 * @brief Concatenate two strings
 * 
 * @param str1 The first string
 * @param str2 The second string
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_concat(String* str1, String* str2, String** str_out);

/**
 * @brief Destroy a string
 * 
 * @param str The string to destroy
 * @return A StringResult
 */
StringResult string_destroy(String* str);

#endif