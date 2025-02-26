/**
 * @file main.c
 * @brief Main file, used to test basec functionality
 */

#include <stdio.h>

#include "ds/basec_string.h"
#include "ds/basec_array.h"

/**
 * @brief Check if a string operation failed
 * 
 * @param result The result of the string operation
 */
void check_string_result(StringResult result) {
    if (result != STRING_SUCCESS) {
        printf("[ERROR] String operation failed: %s\n", string_result_to_string(result));
        exit(1);
    }
}

/**
 * @brief Check if an array operation failed
 * 
 * @param result The result of the array operation
 */
void check_array_result(ArrayResult result) {
    if (result != ARRAY_SUCCESS) {
        printf("[ERROR] Array operation failed: %s\n", array_result_to_string(result));
        exit(1);
    }
}

/**
 * @brief Main function
 * 
 * @return int
 */
int main() {
    // Strings
    String* str1 = NULL;
    String* str2 = NULL;
    String* str3 = NULL;
    StringResult string_result = STRING_SUCCESS;

    // Array
    Array* arr = NULL;
    ArrayResult array_result = ARRAY_SUCCESS;

    // Create strings
    string_result = string_create("Hello, ", 16, &str1);
    check_string_result(string_result);
    string_result = string_create("World", 16, &str2);
    check_string_result(string_result);
    string_result = string_create("!\n", 8, &str3);
    check_string_result(string_result);

    // Create array
    array_result = array_create(sizeof(String*), 3, &arr);
    check_array_result(array_result);

    // Add strings to array
    array_result = array_add(arr, &str1);
    check_array_result(array_result);
    array_result = array_add(arr, &str2);
    check_array_result(array_result);
    array_result = array_add(arr, &str3);
    check_array_result(array_result);

    // Get array size
    size_t arr_size = 0;
    array_result = array_size(arr, &arr_size);
    check_array_result(array_result);

    // Create concat string
    String* concat_str = NULL;
    string_result = string_create("", 64, &concat_str);
    check_string_result(string_result);

    // Concatenate strings
    for (size_t i = 0; i < arr_size; i++) {
        // Get string from array
        String* str_i = NULL;
        array_result = array_get(arr, i, &str_i);
        check_array_result(array_result);

        // Concatenate strings
        String* tmp_str = NULL;
        string_result = string_concat(concat_str, str_i, &tmp_str);
        check_string_result(string_result);

        // Destroy previous concat string
        string_result = string_destroy(&concat_str);
        check_string_result(string_result);

        // Set new concat string
        concat_str = tmp_str;
    }

    // Print concatenated string
    printf("%s", concat_str->data);

    // Destroy array
    array_result = array_destroy(&arr);
    check_array_result(array_result);

    // Destroy strings
    string_result = string_destroy(&str1);
    check_string_result(string_result);
    string_result = string_destroy(&str2);
    check_string_result(string_result);
    string_result = string_destroy(&str3);
    check_string_result(string_result);
    string_result = string_destroy(&concat_str);
    check_string_result(string_result);

    return 0;
}