/**
 * @file string.c
 * @brief A simple string implementation
 */
#include "basec_string.h"

/**
 * @brief Create a new string
 * 
 * @param str The string to create
 * @return A pointer to the new string
 */
String* string_create(const char* str) {
    String* string = (String*)malloc(sizeof(String));

    string->data = (char*)malloc(strlen(str) + 1);
    strcpy(string->data, str);
    string->length = strlen(str);

    return string;
}

/**
 * @brief Get the length of a string
 * 
 * @param str The string to get the length of
 * @return The length of the string
 */
size_t string_length(const String* str) {
    return str->length;
}

/**
 * @brief Destroy a string
 * 
 * @param str The string to destroy
 */
void string_destroy(String* str) {
    free(str->data);
    free(str);
}