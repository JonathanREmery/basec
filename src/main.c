#include <stdio.h>

#include "basec_string.h"

/**
 * @brief Main function
 * 
 * @return int
 */
int main() {
    // Create a new string
    String* str = NULL;
    StringResult result_create = string_create("Hello, World!", &str);

    // Check if the string was created successfully
    if (result_create != STRING_SUCCESS) {
        printf("[ERROR] %s\n", string_result_to_string(result_create));
        return 1;
    }

    // Print the string
    printf("[INFO] String: %s\n", str->data);

    // Get the length of the string
    size_t length = 0;
    StringResult result_length = string_length(str, &length);

    // Check if the length was retrieved successfully
    if (result_length != STRING_SUCCESS) {
        printf("[ERROR] %s\n", string_result_to_string(result_length));
        return 1;
    }

    // Print the length of the string
    printf("[INFO] Length: %zu\n", length);

    // Destroy the string
    string_destroy(str);

    return 0;
}