/**
 * @file basec_string.h
 * @brief String implementation for basec
 */

#ifndef BASEC_STRING_H
#define BASEC_STRING_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "basec_types.h"
#include "ds/basec_array.h"

/**
 * @brief A string
 */
typedef struct {
    c_str data;
    u64   length;
    u64   capacity;
} BasecString;

/**
 * @brief A result for a string operation
 */
typedef enum {
    BASEC_STRING_SUCCESS,
    BASEC_STRING_NULL_POINTER,
    BASEC_STRING_ALLOCATION_FAILURE,
    BASEC_STRING_MEMOP_FAILURE,
    BASEC_STRING_NOT_FOUND,
    BASEC_STRING_ARRAY_FAILURE,
} BasecStringResult;

/**
 * @brief Handle a string result
 * @param result The result to handle
 */
void basec_string_handle_result(BasecStringResult result);

/**
 * @brief Create a new string
 * @param string The string to create
 * @param str The c_str to create the string from
 * @param capacity The capacity of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_create(BasecString** string, const c_str str, u64 capacity);

/**
 * @brief Get the string as a c_str
 * @param string The string to get
 * @param str_out The c_str to store the string in
 * @return The result of the operation
 */
BasecStringResult basec_string_c_str(BasecString* string, c_str* str_out);

/**
 * @brief Get the length of the string
 * @param string The string to get the length of
 * @param length_out The length of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_length(BasecString* string, u64* length_out);

/**
 * @brief Get the capacity of the string
 * @param string The string to get the capacity of
 * @param capacity_out The capacity of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_capacity(BasecString* string, u64* capacity_out);

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend The string to prepend
 * @return The result of the operation
 */
BasecStringResult basec_string_prepend(BasecString* string, const c_str prepend);

/**
 * @brief Find a substring in the string
 * @param string The string to find the substring in
 * @param substr The substring to find
 * @param index_out The index of the substring
 * @return The result of the operation
 */
BasecStringResult basec_string_find(BasecString* string, const c_str substr, u64* index_out);

/**
 * @brief Append a string to the string
 * @param string The string to append to
 * @param append The string to append
 * @return The result of the operation
 */
BasecStringResult basec_string_append(BasecString* string, const c_str append);

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
);

/**
 * @brief Destroy a string
 * @param string The string to destroy
 * @return The result of the operation
 */
BasecStringResult basec_string_destroy(BasecString** string);

/**
 * @brief Destroy an array of strings
 * @param string_arr The array of strings to destroy
 * @return The result of the operation
 */
BasecStringResult basec_strings_destroy(BasecArray** string_arr);

#endif