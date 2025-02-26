/**
 * @file basec_string.h
 * @brief Declaration of a String type and functions
 */
#ifndef BASEC_STRING_H
#define BASEC_STRING_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Result of a string operation
 */
typedef enum {
    STRING_SUCCESS,            //< The operation was successful
    STRING_ERROR_NULL_POINTER, //< A NULL pointer was passed to the function
    STRING_ERROR_INVALID_CAPACITY, //< The capacity is invalid
    STRING_ERROR_CAPACITY_TOO_SMALL, //< The capacity is too small
    STRING_ERROR_MALLOC,       //< The memory allocation failed
    STRING_ERROR_REALLOC,      //< The memory reallocation failed
    STRING_ERROR_MEMCPY,       //< The memcpy failed
    STRING_ERROR_EMPTY,        //< The string is empty
    STRING_ERROR_NOT_FOUND     //< The substring is not found
} StringResult;

/**
 * @brief String type
 */
typedef struct {
    char*  data;     //< The string data
    size_t length;   //< The length of the string
    size_t capacity; //< The capacity of the string
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
 * @param capacity The capacity of the string
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_create(const char* str, size_t capacity, String** str_out);

/**
 * @brief Resize the capacity of a string
 * 
 * @param str The string to resize
 * @param new_capacity The new capacity
 * @return A StringResult
 */
StringResult string_resize(String* str, size_t new_capacity);

/**
 * @brief Set the value of a string
 * 
 * @param str The string to set
 * @param value The value to set the string to
 * @return A StringResult
 */
StringResult string_set(String* str, const char* value);

/**
 * @brief Get the length of a string
 * 
 * @param str The string to get the length of
 * @param length_out The output length
 * @return A StringResult
 */
StringResult string_length(const String* str, size_t* length_out);

/**
 * @brief Get the capacity of a string
 * 
 * @param str The string to get the capacity of
 * @param capacity_out The output capacity
 * @return A StringResult
 */
StringResult string_capacity(const String* str, size_t* capacity_out);

/**
 * @brief Copy a string
 * 
 * @param str The string to copy
 * @param str_out The output string
 * @return A StringResult
 */
StringResult string_copy(String* str, String** str_out);

/**
 * @brief Append a string to another string
 * 
 * @param str The string to append to
 * @param substr The string to append
 * @return A StringResult
 */
StringResult string_append(String* str, String* substr);

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
 * @brief Check if a string contains another string
 * 
 * @param str The string to check
 * @param substr The substring to check for
 * @param contains_out The output contains
 * @return A StringResult
 */
StringResult string_contains(String* str, String* substr, bool* contains_out);

/**
 * @brief Get the index of a substring in a string
 * 
 * @param str The string to check
 * @param substr The substring to check for
 * @param index_out The output index
 * @return A StringResult
 */
StringResult string_index_of(String* str, String* substr, size_t* index_out);

/**
 * @brief Destroy a string
 * 
 * @param str_ptr A pointer to the string to destroy
 * @return A StringResult
 */
StringResult string_destroy(String** str_ptr);

#endif