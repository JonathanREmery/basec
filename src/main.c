#include <stdio.h>

#include "basec_string.h"

/**
 * @brief Main function
 * 
 * @return int
 */
int main() {
    // Create a new string
    String* str = string_create("Hello, World!");

    // Print the string and its length
    printf("String: %s\n", str->data);
    printf("Length: %zu\n", string_length(str));

    // Destroy the string
    string_destroy(str);

    return 0;
}