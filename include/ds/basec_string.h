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
    STRING_SUCCESS,                 //< Success
    STRING_ERROR_NULL_POINTER,      //< NULL pointer
    STRING_ERROR_INVALID_CAPACITY,  //< Invalid capacity
    STRING_ERROR_CAPACITY_EXCEEDED, //< Capacity exceeded
    STRING_ERROR_MALLOC,            //< Malloc failed
    STRING_ERROR_REALLOC,           //< Realloc failed
    STRING_ERROR_MEMCPY,            //< Memcpy failed
    STRING_ERROR_EMPTY,             //< Empty string
    STRING_FOUND,                   //< Found
    STRING_ERROR_NOT_FOUND          //< Not found
} StringResult;

/**
 * @brief String type
 */
typedef struct {
    char*  data;     //< Data
    size_t length;   //< Length
    size_t capacity; //< Capacity
} String;

/**
 * @brief Convert a StringResult to a string
 * 
 * @param result StringResult to convert
 * @return       String representation of the StringResult
 */
const char* string_result_to_string(StringResult result);

/**
 * @brief Create a new string
 * 
 * @param str      String data
 * @param capacity Capacity of the string
 * @param str_out  Output string
 * @return         StringResult
 */
StringResult string_create(const char* str, size_t capacity, String** str_out);

/**
 * @brief Resize the capacity of a string
 * 
 * @param str          String to resize
 * @param new_capacity New capacity
 * @return             StringResult
 */
StringResult string_resize(String* str, size_t new_capacity);

/**
 * @brief Set the value of a string
 * 
 * @param str   String to set
 * @param value Value to set the string to
 * @return      StringResult
 */
StringResult string_set(String* str, const char* value);

/**
 * @brief Get the length of a string
 * 
 * @param str        String to get the length of
 * @param length_out Output length
 * @return           StringResult
 */
StringResult string_length(const String* str, size_t* length_out);

/**
 * @brief Get the capacity of a string
 * 
 * @param str          String to get the capacity of
 * @param capacity_out Output capacity
 * @return             StringResult
 */
StringResult string_capacity(const String* str, size_t* capacity_out);

/**
 * @brief Copy a string
 * 
 * @param str     String to copy
 * @param str_out Output string
 * @return        StringResult
 */
StringResult string_copy(String* str, String** str_out);

/**
 * @brief Append a string to another string
 * 
 * @param str1 String to append to
 * @param str2 String to append
 * @return     StringResult
 */
StringResult string_append(String* str1, String* str2);

/**
 * @brief Concatenate two strings
 * 
 * @param str1    First string
 * @param str2    Second string
 * @param str_out Output string
 * @return        StringResult
 */
StringResult string_concat(String* str1, String* str2, String** str_out);

/**
 * @brief Check if a string contains another string
 * 
 * @param str          String to check
 * @param substr       Substring to check for
 * @param contains_out Output contains
 * @return             StringResult
 */
StringResult string_contains(String* str, String* substr, bool* contains_out);

/**
 * @brief Get the index of a substring in a string
 * 
 * @param str       String to check
 * @param substr    Substring to check for
 * @param index_out Output index
 * @return          StringResult
 */
StringResult string_index_of(String* str, String* substr, size_t* index_out);

/**
 * @brief Destroy a string
 * 
 * @param str_ptr String to destroy
 * @return        StringResult
 */
StringResult string_destroy(String** str_ptr);

#endif