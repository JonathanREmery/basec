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
    BASEC_STRING_FAILURE,
} BasecStringResult;

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
BasecStringResult basec_string_c_str(BasecString** string, c_str* str_out);

/**
 * @brief Get the length of the string
 * @param string The string to get the length of
 * @param length_out The length of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_length(BasecString** string, u64* length_out);

/**
 * @brief Get the capacity of the string
 * @param string The string to get the capacity of
 * @param capacity_out The capacity of the string
 * @return The result of the operation
 */
BasecStringResult basec_string_capacity(BasecString** string, u64* capacity_out);

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend The string to prepend
 * @return The result of the operation
 */
BasecStringResult basec_string_prepend(BasecString** string, const c_str prepend);

/**
 * @brief Append a string to the string
 * @param string The string to append to
 * @param append The string to append
 * @return The result of the operation
 */
BasecStringResult basec_string_append(BasecString** string, const c_str append);

/**
 * @brief Destroy a string
 * @param string The string to destroy
 * @return The result of the operation
 */
BasecStringResult basec_string_destroy(BasecString** string);

#endif