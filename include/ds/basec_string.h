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
 * @brief Create a new string
 * @param str The string to create
 * @param capacity The capacity of the string
 * @return A pointer to the new string
 */
BasecString* basec_string_create(const c_str str, u64 capacity);

/**
 * @brief Get the string as a c_str
 * @param string The string to get
 * @return The string as a c_str
 */
c_str basec_string_c_str(BasecString* string);

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend The string to prepend
 */
void basec_string_prepend(BasecString* string, const c_str prepend);

/**
 * @brief Append a string to the string
 * @param string The string to append to
 * @param append The string to append
 */
void basec_string_append(BasecString* string, const c_str append);

/**
 * @brief Destroy a string
 * @param string The string to destroy
 */
void basec_string_destroy(BasecString* string);

#endif