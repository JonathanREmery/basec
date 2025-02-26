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
    printf("[INFO] String Data: %s\n", str->data);

    // Get the length of the string
    size_t length = 0;
    StringResult result_string_length = string_length(str, &length);

    // Check if the length was retrieved successfully
    if (result_string_length != STRING_SUCCESS) {
        printf("[ERROR] %s\n", string_result_to_string(result_string_length));
        return 1;
    }

    // Print the length of the string
    printf("[INFO] String Length: %zu\n", length);

    // Destroy the string
    StringResult result_string_destroy = string_destroy(&str);

    // Check if the string was destroyed successfully
    if (result_string_destroy != STRING_SUCCESS) {
        printf("[ERROR] %s\n", string_result_to_string(result_string_destroy));
        return 1;
    }

    // Create a new array
    Array* array = NULL;
    ArrayResult result_array_create = array_create(10, sizeof(int), &array);

    // Check if the array was created successfully
    if (result_array_create != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_create));
        return 1;
    }

    // Add an element to the array
    int element = 10;
    ArrayResult result_array_add = array_add(array, &element);

    // Check if the element was added successfully
    if (result_array_add != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_add));
        return 1;
    }

    // Get the size of the array
    size_t size = 0;
    ArrayResult result_array_size = array_size(array, &size);

    // Check if the size was retrieved successfully
    if (result_array_size != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_size));
        return 1;
    }

    // Print the size of the array
    printf("[INFO] Array Size: %zu\n", size);

    // Get the capacity of the array
    size_t capacity = 0;
    ArrayResult result_array_capacity = array_capacity(array, &capacity);

    // Check if the capacity was retrieved successfully
    if (result_array_capacity != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_capacity));
        return 1;
    }

    // Print the capacity of the array
    printf("[INFO] Array Capacity: %zu\n", capacity);

    // Set an element in the array
    int new_element = 20;
    ArrayResult result_array_set = array_set(array, 0, &new_element);

    // Check if the element was set successfully
    if (result_array_set != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_set));
        return 1;
    }

    // Get the element from the array
    int element_out = 0;
    ArrayResult result_array_get = array_get(array, 0, &element_out);

    // Check if the element was retrieved successfully
    if (result_array_get != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_get));
        return 1;
    }

    // Print the element from the array
    printf("[INFO] Array Element: %d\n", element_out);

    // Remove an element from the array
    ArrayResult result_array_remove = array_remove(array, 0);

    // Check if the element was removed successfully
    if (result_array_remove != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_remove));
        return 1;
    }

    // Get the size of the array
    size_t size_after_remove = 0;
    ArrayResult result_array_size_after_remove = array_size(array, &size_after_remove);

    // Check if the size was retrieved successfully
    if (result_array_size_after_remove != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_size_after_remove));
        return 1;
    }

    // Print the size of the array after removal
    printf("[INFO] Array Size After Removal: %zu\n", size_after_remove);

    // Destroy the array
    ArrayResult result_array_destroy = array_destroy(&array);

    // Check if the array was destroyed successfully
    if (result_array_destroy != ARRAY_SUCCESS) {
        printf("[ERROR] %s\n", array_result_to_string(result_array_destroy));
        return 1;
    }

    return 0;
}