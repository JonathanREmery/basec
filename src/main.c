/**
 * @file main.c
 * @brief Main file, used to test basec functionality
 */

#include <stdio.h>

#include "ds/string/basec_string.h"
#include "ds/array/basec_array.h"

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

    // String results
    StringResult result_string_create = STRING_SUCCESS;
    StringResult result_string_concat = STRING_SUCCESS;
    StringResult result_string_destroy = STRING_SUCCESS;

    // Array
    Array* arr = NULL;

    // Array results
    ArrayResult result_array_create = ARRAY_SUCCESS;
    ArrayResult result_array_add = ARRAY_SUCCESS;
    ArrayResult result_array_size = ARRAY_SUCCESS;
    ArrayResult result_array_get = ARRAY_SUCCESS;
    ArrayResult result_array_destroy = ARRAY_SUCCESS;

    // Create strings
    result_string_create = string_create("Hello, ", &str1);
    check_string_result(result_string_create);
    result_string_create = string_create("World", &str2);
    check_string_result(result_string_create);
    result_string_create = string_create("!\n", &str3);
    check_string_result(result_string_create);

    // Create array
    result_array_create = array_create(3, sizeof(String*), &arr);
    check_array_result(result_array_create);

    // Add strings to array
    result_array_add = array_add(arr, &str1);
    check_array_result(result_array_add);
    result_array_add = array_add(arr, &str2);
    check_array_result(result_array_add);
    result_array_add = array_add(arr, &str3);
    check_array_result(result_array_add);

    // Get array size
    size_t arr_size = 0;
    result_array_size = array_size(arr, &arr_size);
    check_array_result(result_array_size);

    // Create concat string
    String* concat_str = NULL;
    result_string_create = string_create("", &concat_str);
    check_string_result(result_string_create);

    // Concatenate strings
    for (size_t i = 0; i < arr_size; i++) {
        // Get string from array
        String* str_i = NULL;
        result_array_get = array_get(arr, i, &str_i);
        check_array_result(result_array_get);

        // Concatenate strings
        String* tmp_str = NULL;
        result_string_concat = string_concat(concat_str, str_i, &tmp_str);
        check_string_result(result_string_concat);

        // Destroy previous concat string
        result_string_destroy = string_destroy(&concat_str);
        check_string_result(result_string_destroy);

        // Set new concat string
        concat_str = tmp_str;
    }

    // Print concatenated string
    printf("%s", concat_str->data);

    // Destroy array
    result_array_destroy = array_destroy(&arr);
    check_array_result(result_array_destroy);

    // Destroy strings
    result_string_destroy = string_destroy(&str1);
    check_string_result(result_string_destroy);
    result_string_destroy = string_destroy(&str2);
    check_string_result(result_string_destroy);
    result_string_destroy = string_destroy(&str3);
    check_string_result(result_string_destroy);
    result_string_destroy = string_destroy(&concat_str);
    check_string_result(result_string_destroy);

    return 0;
}