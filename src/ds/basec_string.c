/**
 * @file basec_string.c
 * @brief Implementation of a String type and functions
 */

#include "ds/basec_string.h"

/**
 * @brief Convert a StringResult to a string
 * 
 * @param result StringResult to convert
 * @return       String representation of the StringResult
 */
const char* string_result_to_string(StringResult result) {
    switch (result) {
        case STRING_SUCCESS:
            return "STRING_SUCCESS";                 //< Success
        case STRING_ERROR_NULL_POINTER:
            return "STRING_ERROR_NULL_POINTER";      //< NULL pointer
        case STRING_ERROR_INVALID_CAPACITY:
            return "STRING_ERROR_INVALID_CAPACITY";  //< Invalid capacity
        case STRING_ERROR_CAPACITY_EXCEEDED:
            return "STRING_ERROR_CAPACITY_EXCEEDED"; //< Capacity exceeded
        case STRING_ERROR_MALLOC:
            return "STRING_ERROR_MALLOC";            //< Malloc failed
        case STRING_ERROR_REALLOC:
            return "STRING_ERROR_REALLOC";           //< Realloc failed
        case STRING_ERROR_MEMCPY:
            return "STRING_ERROR_MEMCPY";            //< Memcpy failed
        case STRING_ERROR_EMPTY:
            return "STRING_ERROR_EMPTY";             //< Empty string
        case STRING_FOUND:
            return "STRING_FOUND";                   //< Found
        case STRING_ERROR_NOT_FOUND:
            return "STRING_ERROR_NOT_FOUND";         //< Not found
        default:
            return "UNKNOWN_STRING_RESULT";          //< Unknown result
    }
}

/**
 * @brief Create a new string
 * 
 * @param str      String data
 * @param capacity Capacity of the string
 * @param str_out  Output string
 * @return         StringResult
 */
StringResult string_create(const char* str, size_t capacity, String** str_out) {
    // Check the validity of the string data, capacity, and output string
    if (str == NULL || str_out == NULL) return STRING_ERROR_NULL_POINTER;
    if (capacity < 1) return STRING_ERROR_INVALID_CAPACITY;

    // Allocate memory for the string
    String* string = (String*)malloc(sizeof(String));

    // Check if the allocation failed
    if (string == NULL) return STRING_ERROR_MALLOC;

    // Allocate memory for the string data
    string->data = (char*)malloc(capacity + 1);

    // Check if the allocation failed
    if (string->data == NULL) {
        // Free the string structure
        free(string);

        // Set the output string to NULL
        *str_out = NULL;

        // Malloc failed
        return STRING_ERROR_MALLOC;
    }

    // Set the capacity
    string->capacity = capacity;

    // Get the length of the string
    string->length = strlen(str);

    // Check if the length exceeds the capacity
    if (string->length >= capacity) {
        // Free the string structure
        free(string);

        // Set the output string to NULL
        *str_out = NULL;

        // Capacity exceeded
        return STRING_ERROR_CAPACITY_EXCEEDED;
    }

    // Copy the string data
    void* memcpy_result = memcpy(string->data, str, string->length);

    // Check if the copy failed
    if (memcpy_result == NULL) {
        // Free the string structure
        free(string);

        // Set the output string to NULL
        *str_out = NULL;

        // Memcpy failed
        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    string->data[string->length] = '\0';

    // Set the output string
    *str_out = string;

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Resize the capacity of a string
 * 
 * @param str          String to resize
 * @param new_capacity New capacity
 * @return             StringResult
 */
StringResult string_resize(String* str, size_t new_capacity) {
    // Check for NULL pointer
    if (str == NULL) return STRING_ERROR_NULL_POINTER;

    // Check if the new capacity is invalid
    if (new_capacity < 1 || new_capacity < str->length) {
        // Invalid capacity
        return STRING_ERROR_INVALID_CAPACITY;
    }
    
    // Check if the new capacity is smaller than the current capacity
    if (new_capacity <= str->capacity) {
        // Update the capacity
        str->capacity = new_capacity;

        // Success
        return STRING_SUCCESS;
    }

    // Reallocate memory for the string
    str->data = (char*)realloc(str->data, new_capacity + 1);

    // Check if the reallocation failed
    if (str->data == NULL) return STRING_ERROR_REALLOC;

    // Update the capacity
    str->capacity = new_capacity;

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Set the value of a string
 * 
 * @param str   String to set
 * @param value Value to set the string to
 * @return      StringResult
 */
StringResult string_set(String* str, const char* value) {
    // Check for NULL pointers
    if (str == NULL || value == NULL) return STRING_ERROR_NULL_POINTER;

    // Check if the strings are the same
    if (strcmp(str->data, value) == 0) return STRING_SUCCESS;

    // Calculate the new length of the string
    size_t new_length = strlen(value);

    // Check if string needs to be grown
    if (new_length >= str->capacity) {
        // Resize the string to double the new length
        StringResult resize_result = string_resize(str, new_length * 2);

        // Check if the resize failed
        if (resize_result != STRING_SUCCESS) {
            // Resize failed
            return resize_result;
        }
    }

    // Set the length of the string
    str->length = new_length;

    // Copy the value to the string
    void* memcpy_result = memcpy(str->data, value, str->length);

    // Check if the copy failed
    if (memcpy_result == NULL) return STRING_ERROR_MEMCPY;

    // Null-terminate the string
    str->data[str->length] = '\0';

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Get the length of a string
 * 
 * @param str        String to get the length of
 * @param length_out Output length
 * @return           StringResult
 */
StringResult string_length(const String* str, size_t* length_out) {
    // Check for NULL pointers
    if (str == NULL || length_out == NULL) return STRING_ERROR_NULL_POINTER;

    // Set the output length
    *length_out = str->length;

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Get the capacity of a string
 * 
 * @param str          String to get the capacity of
 * @param capacity_out Output capacity
 * @return             StringResult
 */
StringResult string_capacity(const String* str, size_t* capacity_out) {
    // Check for NULL pointers
    if (str == NULL || capacity_out == NULL) return STRING_ERROR_NULL_POINTER;

    // Set the output capacity
    *capacity_out = str->capacity;

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Copy a string
 * 
 * @param str     String to copy
 * @param str_out Output string
 * @return        StringResult
 */
StringResult string_copy(String* str, String** str_out) {
    // Check for NULL pointers
    if (str == NULL || str_out == NULL) return STRING_ERROR_NULL_POINTER;

    // Allocate memory for the string structure
    *str_out = (String*)malloc(sizeof(String));

    // Check if the allocation failed
    if (*str_out == NULL) return STRING_ERROR_MALLOC;

    // Allocate memory for the string data
    (*str_out)->data = (char*)malloc(str->length + 1);

    // Check if the allocation failed
    if ((*str_out)->data == NULL) {
        // Free the string structure
        free(*str_out);

        // Set the output string to NULL
        *str_out = NULL;

        // Malloc failed
        return STRING_ERROR_MALLOC;
    }

    // Set the length and capacity of the copied string
    (*str_out)->length = str->length;
    (*str_out)->capacity = str->capacity;

    // Copy the string data
    void* memcpy_result = memcpy((*str_out)->data, str->data, str->length);

    // Check if the copy failed
    if (memcpy_result == NULL) {
        // Free the string structure
        free(*str_out);

        // Set the output string to NULL
        *str_out = NULL;

        // Memcpy failed
        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    (*str_out)->data[str->length] = '\0';

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Append a string to another string
 * 
 * @param str1   String to append to
 * @param str2   String to append
 * @return       StringResult
 */
StringResult string_append(String* str1, String* str2) {
    // Check for the validity of the strings
    if (str1 == NULL || str2 == NULL) return STRING_ERROR_NULL_POINTER;
    if (str2->length == 0) return STRING_SUCCESS;

    // Calculate the new length of the string
    size_t new_length = str1->length + str2->length;

    // Check if the string needs to be grown
    if (new_length >= str1->capacity) {
        // Resize the string to double the new length
        StringResult resize_result = string_resize(str1, new_length * 2);

        // Check if the resize failed
        if (resize_result != STRING_SUCCESS) {
            // Resize failed
            return resize_result;
        }
    }

    // Set the length of the string
    str1->length = new_length;

    // Copy the str2 to the end of the str1
    void* memcpy_result = memcpy(
        str1->data + str1->length - str2->length,
        str2->data,
        str2->length
    );

    // Check if the copy failed
    if (memcpy_result == NULL) return STRING_ERROR_MEMCPY;

    // Null-terminate the string
    str1->data[str1->length] = '\0';

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Concatenate two strings
 * 
 * @param str1    First string
 * @param str2    Second string
 * @param str_out Output string
 * @return        StringResult
 */
StringResult string_concat(String* str1, String* str2, String** str_out) {
    // Check for NULL pointers
    if (str1 == NULL || str2 == NULL || str_out == NULL) {
        // NULL pointer
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if either string is empty
    if (str1->length == 0) return string_copy(str2, str_out);
    if (str2->length == 0) return string_copy(str1, str_out);

    // Allocate memory for the concatenated string structure
    String* concat_str = (String*)malloc(sizeof(String));

    // Check if the allocation failed
    if (concat_str == NULL) {
        // Set the output string to NULL
        *str_out = NULL;

        // Malloc failed
        return STRING_ERROR_MALLOC;
    }

    // Calculate total length and capacity
    size_t total_length = str1->length + str2->length;
    size_t total_capacity = total_length * 2;

    // Allocate memory for the concatenated string data
    concat_str->data = (char*)malloc(total_capacity);

    // Check if the allocation failed
    if (concat_str->data == NULL) {
        // Free the string structure
        free(concat_str);

        // Set the output string to NULL
        *str_out = NULL;

        // Malloc failed
        return STRING_ERROR_MALLOC;
    }

    // Copy the first string
    void* memcpy_result = memcpy(concat_str->data, str1->data, str1->length);

    // Check if the copy failed
    if (memcpy_result == NULL) {
        // Free the string structure
        free(concat_str);

        // Set the output string to NULL
        *str_out = NULL;

        // Memcpy failed
        return STRING_ERROR_MEMCPY;
    }

    // Copy the second string
    memcpy_result = memcpy(
        concat_str->data + str1->length,
        str2->data,
        str2->length
    );

    // Check if the copy failed
    if (memcpy_result == NULL) {
        // Free the string structure
        free(concat_str);

        // Set the output string to NULL
        *str_out = NULL;

        // Memcpy failed
        return STRING_ERROR_MEMCPY;
    }

    // Null-terminate the string
    concat_str->data[total_length] = '\0';

    // Set the length and capacity of the concatenated string
    concat_str->length = total_length;
    concat_str->capacity = total_capacity;

    // Set the output string
    *str_out = concat_str;

    // Success
    return STRING_SUCCESS;
}

/**
 * @brief Check if a string contains another string
 * 
 * @param str          String to check
 * @param substr       Substring to check for
 * @param contains_out Output contains
 * @return             StringResult
 */
StringResult string_contains(String* str, String* substr, bool* contains_out) {
    // Check for NULL pointers
    if (str == NULL || substr == NULL || contains_out == NULL) {
        // Set the output contains to false if it is not NULL
        if (contains_out != NULL) *contains_out = false;

        // NULL pointer
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if the substring is empty
    if (substr->length == 0) {
        // Set the output contains to false
        *contains_out = false;

        // Empty string
        return STRING_ERROR_EMPTY;
    }

    // Check if the substring is contained in the string
    char* strstr_result = strstr(str->data, substr->data);
    if (strstr_result == NULL) {
        // Set the output contains to false
        *contains_out = false;

        // Not found
        return STRING_ERROR_NOT_FOUND;
    }

    // Set the output contains to true
    *contains_out = true;

    // Found
    return STRING_FOUND;
}

/**
 * @brief Get the index of a substring in a string
 * 
 * @param str       String to check
 * @param substr    Substring to check for
 * @param index_out Output index
 * @return          StringResult
 */
StringResult string_index_of(String* str, String* substr, size_t* index_out) {
    // Check for NULL pointers
    if (str == NULL || substr == NULL || index_out == NULL) {
        // Set the output index to UINT64_MAX if it is not NULL
        if (index_out != NULL) *index_out = __UINT64_MAX__;

        // NULL pointer
        return STRING_ERROR_NULL_POINTER;
    }

    // Check if the substring is empty
    if (substr->length == 0) {
        // Set the output index to UINT64_MAX
        *index_out = __UINT64_MAX__;

        // Empty string
        return STRING_ERROR_EMPTY;
    }

    // Check if the substring is contained in the string
    char* strstr_result = strstr(str->data, substr->data);
    if (strstr_result == NULL) {
        // Set the output index to UINT64_MAX
        *index_out = __UINT64_MAX__;

        // Substring not found
        return STRING_ERROR_NOT_FOUND;
    }

    // Set the output index
    *index_out = strstr_result - str->data;

    // Found
    return STRING_FOUND;
}

/**
 * @brief Destroy a string
 * 
 * @param str_ptr String to destroy
 * @return        StringResult
 */
StringResult string_destroy(String** str_ptr) {
    // Check if the string is NULL
    if (str_ptr == NULL || *str_ptr == NULL) return STRING_ERROR_NULL_POINTER;

    // Free the string data
    free((*str_ptr)->data);

    // Free the string structure
    free(*str_ptr);

    // Set the string to NULL
    *str_ptr = NULL;

    // Success
    return STRING_SUCCESS;
}
