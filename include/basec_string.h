/**
 * @file string.h
 * @brief A simple string implementation
 */
#ifndef BASEC_STRING_H
#define BASEC_STRING_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief A simple string implementation
 */
typedef struct {
    char* data;
    size_t length;
} String;

/**
 * @brief Create a new string
 * 
 * @param str The string to create
 * @return A pointer to the new string
 */
String* string_create(const char* str);

/**
 * @brief Get the length of a string
 * 
 * @param str The string to get the length of
 * @return The length of the string
 */
size_t string_length(const String* str);


/**
 * @brief Destroy a string
 * 
 * @param str The string to destroy
 */
void string_destroy(String* str);

#endif