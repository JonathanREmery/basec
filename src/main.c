#include <stdio.h>

#include "ds/string/basec_string.h"
#include "ds/array/basec_array.h"

/**
 * @brief Main function
 * 
 * @return int
 */
int main() {
    // Create a new string
    String* str = NULL;
    StringResult result_string_create = string_create("Hello, World!", &str);

    // Check if the string was created successfully
    if (result_string_create != STRING_SUCCESS) {
        printf("[ERROR] %s\n", string_result_to_string(result_string_create));
        return 1;
    }

    // Print the string
    printf("[INFO] String: %s\n", str->data);

    // Get the length of the string
    size_t length = 0;
    StringResult result_string_length = string_length(str, &length);

    // Check if the length was retrieved successfully
    if (result_string_length != STRING_SUCCESS) {
        printf("[ERROR] %s\n", string_result_to_string(result_string_length));
        return 1;
    }

    // Print the length of the string
    printf("[INFO] Length: %zu\n", length);

    // Destroy the string
    StringResult result_string_destroy = string_destroy(&str);

    // Check if the string was destroyed successfully
    if (result_string_destroy != STRING_SUCCESS) {
        printf("[ERROR] %s\n", string_result_to_string(result_string_destroy));
        return 1;
    }

    // Create a new array
    Array* array = NULL;
    ArrayResult result_array_create = array_create(10, &array);

    // Check if the array was created successfully
    if (result_array_create != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_create));
        return 1;
    }

    // Destroy the array
    ArrayResult result_array_destroy = array_destroy(&array);

    // Check if the array was destroyed successfully
    if (result_array_destroy != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_destroy));
        return 1;
    }
    return 0;
}