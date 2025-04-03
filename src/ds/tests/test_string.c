#include "ds/tests/test_string.h"

/**
 * @brief Test the creation of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_create(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (strncmp(string->data, "Hello, World!", 13) != 0) {
        (void)strncpy(
            fail_message,
            "String data does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (string->length != 13) {
        (void)strncpy(
            fail_message,
            "String length does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (string->capacity != 16) {
        (void)strncpy(
            fail_message,
            "String capacity does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_create(NULL, "Hello, World!", 13);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String creation with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }
    
    string_result = basec_string_create(&string, NULL, 13);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String creation with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }
    
    string_result = basec_string_create(&string, "Hello, World!", 0);
    if (string_result != BASEC_STRING_INVALID_CAPACITY) {
        (void)strncpy(
            fail_message,
            "String creation with invalid capacity succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    return true;
}

/**
 * @brief Test getting the c_str
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_c_str(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;
    c_str             c_str_result  = NULL;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_c_str(string, &c_str_result);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Getting c_str from string failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (strcmp(c_str_result, "Hello, World!") != 0) {
        (void)strncpy(
            fail_message,
            "c_str does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_c_str(NULL, &c_str_result);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting c_str with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_c_str(string, NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting c_str with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
        
    return true;
}

/**
 * @brief Test getting the length of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_length(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;
    u64               length        = 0;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_length(string, &length);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Getting string length failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (length != 13) {
        (void)strncpy(
            fail_message,
            "String length does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_length(NULL, &length);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting length with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_length(string, NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting length with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    return true;
}

/**
 * @brief Test getting the capacity of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_capacity(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;
    u64               capacity      = 0;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_capacity(string, &capacity);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Getting string capacity failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (capacity != 16) {
        (void)strncpy(
            fail_message,
            "String capacity does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_capacity(NULL, &capacity);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting capacity with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_capacity(string, NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting capacity with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    return true;
}

/**
 * @brief Test prepending a string to a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_prepend(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;

    string_result = basec_string_create(&string, "World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_prepend(string, "Hello, ");
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Prepending to string failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (strcmp(string->data, "Hello, World!") != 0) {
        (void)strncpy(
            fail_message,
            "String content does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_prepend(NULL, "Hello, ");
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Prepending with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_prepend(string, NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Prepending with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    return true;
}

/**
 * @brief Test appending a string to a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_append(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;

    string_result = basec_string_create(&string, "Hello, ", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_append(string, "World!");
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Appending to string failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (strcmp(string->data, "Hello, World!") != 0) {
        (void)strncpy(
            fail_message,
            "String content does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_append(NULL, "Hello, ");
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Appending with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_append(string, NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Appending with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    return true;
}

/**
 * @brief Test pushing a string to a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_push(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;

    string_result = basec_string_create(&string, "Hello, ", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_push(string, "World!");
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String push operation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }

    if (strcmp(string->data, "Hello, World!") != 0) {
        (void)strncpy(
            fail_message,
            "String content does not match expected value after push",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_push(NULL, "Hello, ");
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Pushing with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_push(string, NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Pushing with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test checking if a string contains a substring
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_contains(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;
    bool              contains_out  = false;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_contains(string, "World", &contains_out);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Checking for substring failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }

    if (!contains_out) {
        (void)strncpy(
            fail_message,
            "Expected to find substring in the string, but did not",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_contains(string, "NotFound", &contains_out);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Checking for substring failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }

    if (contains_out) {
        (void)strncpy(
            fail_message,
            "Expected not to find substring in the string, but did",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }
    
    string_result = basec_string_contains(NULL, "World", &contains_out);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Checking for substring with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_contains(string, NULL, &contains_out);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Checking for substring with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_contains(string, "World", NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Checking for substring with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test finding a substring in a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_find(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;
    u64               index_out     = 0;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_find(string, "World", &index_out);
    if (string_result != BASEC_STRING_SUCCESS || index_out != 7) {
        (void)strncpy(
            fail_message,
            "Failed to find existing substring",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_find(string, "NotFound", &index_out);
    if (string_result != BASEC_STRING_NOT_FOUND) {
        (void)strncpy(
            fail_message,
            "Found non-existant substring",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&string);
        return false;
    }

    string_result = basec_string_find(NULL, "World", &index_out);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding substring with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_find(string, NULL, &index_out);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding substring with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_find(string, "World", NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding substring with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test finding all instances of a substring in a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_find_all(c_str fail_message) {
    BasecStringResult string_result      = BASEC_STRING_SUCCESS;
    BasecString*      string             = NULL;
    BasecArray*       indices            = NULL;
    BasecArrayResult  array_result       = BASEC_ARRAY_SUCCESS;
    u64               expected_indices[] = {4, 8, 15, 19, 22, 26};

    string_result = basec_string_create(&string, "Hello, World! How do you do?", 32);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_find_all(string, "o", &indices);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Finding all instances failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (indices->length != 6) {
        (void)strncpy(
            fail_message,
            "Unexpected number of instances found",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_array_destroy(&indices);
        return false;
    }
    
    for (u64 i = 0; i < indices->length; i++) {
        u64 index;
        array_result = basec_array_get(indices, i, &index);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Array get failed",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );

            (void)basec_string_destroy(&string);
            (void)basec_array_destroy(&indices);
            return false;
        }

        if (index != expected_indices[i]) {
            (void)strncpy(
                fail_message,
                "Index mismatch",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );

            (void)basec_string_destroy(&string);
            (void)basec_array_destroy(&indices);
            return false;
        }
    } 
    
    string_result = basec_string_find_all(NULL, "o", &indices);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding all instances with NULL string succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_array_destroy(&indices);
        return false;
    }

    string_result = basec_string_find_all(string, NULL, &indices);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding all instances with NULL substring succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_array_destroy(&indices);
        return false;
    }

    string_result = basec_string_find_all(string, "o", NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding all instances with NULL output array succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_array_destroy(&indices);
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_array_destroy(&indices);
        return false;
    }

    array_result = basec_array_destroy(&indices);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Array destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test replacing a substring in a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_replace(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;
    BasecString*      result_string = NULL;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_replace(string, "World", "Universe", &result_string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String replacement failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (strcmp(result_string->data, "Hello, Universe!") != 0) {
        (void)strncpy(
            fail_message,
            "Replacement result does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_string_destroy(&result_string);
        return false;
    }
    
    string_result = basec_string_replace(string, "World", "Universe", &string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "In-place string replacement failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_string_destroy(&result_string);
        return false;
    }
    
    if (strcmp(string->data, "Hello, Universe!") != 0) {
        (void)strncpy(
            fail_message,
            "In-place string replacement result does not match expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_string_destroy(&result_string);
        return false;
    }
    
    string_result = basec_string_replace(NULL, "World", "Universe", &result_string);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String replacement with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_string_destroy(&result_string);
        return false;
    }

    string_result = basec_string_replace(string, NULL, "Universe", &result_string);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String replacement with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_string_destroy(&result_string);
        return false;
    }

    string_result = basec_string_replace(string, "World", NULL, &result_string);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String replacement with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_string_destroy(&result_string);
        return false;
    }

    string_result = basec_string_replace(string, "World", "Universe", NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String replacement with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_string_destroy(&result_string);
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_string_destroy(&result_string);
        return false;
    }

    string_result = basec_string_destroy(&result_string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Result string destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test splitting a string into an array of strings
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_split(c_str fail_message) {
    BasecStringResult string_result    = BASEC_STRING_SUCCESS;
    BasecString*      string           = NULL;
    BasecArray*       result_array     = NULL;
    BasecArrayResult  array_result     = BASEC_ARRAY_SUCCESS;
    BasecString*      part             = NULL;
    const char*       expected_parts[] = {"Hello,", "World!", "How", "are", "you?"};
    BasecArray*       populated_array  = NULL;

    string_result = basec_string_create(&string, "Hello, World! How are you?", 32);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_split(string, " ", &result_array);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String splitting failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        return false;
    }

    if (result_array->length != 5) {
        (void)strncpy(
            fail_message,
            "Unexpected number of split strings",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_strings_destroy(&result_array);
        return false;
    }

    for (u64 i = 0; i < 5; i++) {
        array_result = basec_array_get(result_array, i, &part);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Array get failed",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );

            (void)basec_string_destroy(&string);
            (void)basec_strings_destroy(&result_array);
            return false;
        }

        if (strcmp(part->data, expected_parts[i]) != 0) {
            (void)strncpy(
                fail_message,
                "Split string content mismatch",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );

            (void)basec_string_destroy(&string);
            (void)basec_strings_destroy(&result_array);
            return false;
        }
    }
    
    array_result = basec_array_create(&populated_array, sizeof(u64), 5);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Array creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_strings_destroy(&result_array);
        return false;
    }
    
    for (u64 i = 0; i < 5; i++) {
        array_result = basec_array_append(populated_array, &expected_parts[i]);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Array append failed",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );

            (void)basec_string_destroy(&string);
            (void)basec_strings_destroy(&result_array);
            (void)basec_array_destroy(&populated_array);
            return false;
        }
    }
    
    string_result = basec_string_split(string, " ", &populated_array);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String splitting failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_strings_destroy(&result_array);
        (void)basec_array_destroy(&populated_array);
        return false;
    }
    
    if (populated_array->length != 5) {
        (void)strncpy(
            fail_message,
            "Unexpected number of split strings",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_string_destroy(&string);
        (void)basec_strings_destroy(&result_array);
        (void)basec_array_destroy(&populated_array);
        return false;
    }
    
    for (u64 i = 0; i < 5; i++) {
        array_result = basec_array_get(populated_array, i, &part);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Array get failed",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );

            (void)basec_string_destroy(&string);
            (void)basec_strings_destroy(&result_array);
            (void)basec_array_destroy(&populated_array);
            return false;
        }

        if (strcmp(part->data, expected_parts[i]) != 0) {
            (void)strncpy(
                fail_message,
                "Split string content mismatch",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );

            (void)basec_string_destroy(&string);
            (void)basec_strings_destroy(&result_array);
            (void)basec_array_destroy(&populated_array);
            return false;
        }
    }
    
    string_result = basec_string_split(NULL, " ", &result_array);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String split with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_array_destroy(&populated_array);
        return false;
    }

    string_result = basec_string_split(string, NULL, &result_array);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String split with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_array_destroy(&populated_array);
        return false;
    }

    string_result = basec_string_split(string, " ", NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "String split with NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        (void)basec_array_destroy(&populated_array);
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_strings_destroy(&result_array);
        return false;
    }

    string_result = basec_strings_destroy(&result_array);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Strings array destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );

        (void)basec_array_destroy(&populated_array);
        return false;
    }
    
    array_result = basec_array_destroy(&populated_array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Array destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}


/**
 * @brief Test the destruction of a string
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_string_destroy(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string        = NULL;

    string_result = basec_string_create(&string, "Hello, World!", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String destruction failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (string != NULL) {
        (void)strncpy(
            fail_message,
            "String was non-NULL after destruction",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_destroy(&string);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Double destruction succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_destroy(NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Destroying NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test the destruction of an array of strings
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_strings_destroy(c_str fail_message) {
    BasecStringResult string_result = BASEC_STRING_SUCCESS;
    BasecString*      string1       = NULL;
    BasecString*      string2       = NULL;
    BasecString*      string3       = NULL;
    BasecArrayResult  array_result  = BASEC_ARRAY_SUCCESS;
    BasecArray*       string_array  = NULL;

    string_result = basec_string_create(&string1, "String 1", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_create(&string2, "String 2", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    string_result = basec_string_create(&string3, "String 3", 16);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "String creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_create(&string_array, sizeof(BasecString*), 3);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Array creation failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }


    array_result = basec_array_append(string_array, &string1);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to add string to array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_append(string_array, &string2);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to add string to array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_append(string_array, &string3);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to add string to array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_strings_destroy(&string_array);
    if (string_result != BASEC_STRING_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy the array of strings",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (string_array != NULL) {
        (void)strncpy(
            fail_message,
            "Array was non-NULL after destruction",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    string_result = basec_string_destroy(NULL);
    if (string_result != BASEC_STRING_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Destroying NULL pointer succeeded, but should fail",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Add String tests to a test suite
 * @param test_suite The test suite to add the tests to
 * @return The result of the operation
 */
BasecTestResult test_string_add_tests(BasecTestSuite* test_suite) {
    BasecTestResult  test_result        = BASEC_TEST_SUCCESS;
    BasecTest*       create_test        = NULL;
    BasecTest*       c_str_test         = NULL;
    BasecTest*       length_test        = NULL;
    BasecTest*       capacity_test      = NULL;
    BasecTest*       prepend_test       = NULL;
    BasecTest*       append_test        = NULL;
    BasecTest*       push_test          = NULL;
    BasecTest*       contains_test      = NULL;
    BasecTest*       find_test          = NULL;
    BasecTest*       find_all_test      = NULL;
    BasecTest*       replace_test       = NULL;
    BasecTest*       split_test         = NULL;
    BasecTest*       destroy_test       = NULL;
    BasecTest*       destroy_array_test = NULL;
    BasecTestModule* string_module      = NULL;

    test_result = basec_test_create(
        &create_test,
        "test_string_create",
        "Test the creation of a string",
        &test_string_create
    );
    if (test_result != BASEC_TEST_SUCCESS) return test_result;
    
    test_result = basec_test_create(
        &c_str_test,
        "test_string_c_str",
        "Test getting the c_str",
        &test_string_c_str
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &length_test,
        "test_string_length",
        "Test getting the length of a string",
        &test_string_length
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &capacity_test,
        "test_string_capacity",
        "Test getting the capacity of a string",
        &test_string_capacity
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &prepend_test,
        "test_string_prepend",
        "Test prepending a string to a string",
        &test_string_prepend
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &append_test,
        "test_string_append",
        "Test appending a string to a string",
        &test_string_append
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &push_test,
        "test_string_push",
        "Test pushing a string to a string",
        &test_string_push
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &contains_test,
        "test_string_contains",
        "Test checking if a string contains a substring",
        &test_string_contains
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &find_test,
        "test_string_find",
        "Test finding a substring in a string",
        &test_string_find
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &find_all_test,
        "test_string_find_all",
        "Test finding all instances of a substring in a string",
        &test_string_find_all
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &replace_test,
        "test_string_replace",
        "Test replacing a substring in a string",
        &test_string_replace
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &split_test,
        "test_string_split",
        "Test splitting a string into an array of strings",
        &test_string_split
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        return test_result;
    }

    test_result = basec_test_create(
        &destroy_test,
        "test_string_destroy",
        "Test the destruction of a string",
        &test_string_destroy
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &destroy_array_test,
        "test_strings_destroy",
        "Test the destruction of an array of strings",
        &test_strings_destroy
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        return test_result;
    }
    
    test_result = basec_test_module_create(
        &string_module,
        "String"
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        return test_result;
    }

    test_result = basec_test_module_add_test(string_module, create_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, c_str_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&c_str_test);
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, length_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&length_test);
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, capacity_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&capacity_test);
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, prepend_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&prepend_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, append_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, push_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, contains_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, find_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, find_all_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, replace_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&replace_test);
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, split_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&split_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }

    test_result = basec_test_module_add_test(string_module, destroy_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(string_module, destroy_array_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&destroy_array_test);
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }
    
    test_result = basec_test_suite_add_module(test_suite, string_module);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_module_destroy(&string_module);
        return test_result;
    }

    return BASEC_TEST_SUCCESS;
}