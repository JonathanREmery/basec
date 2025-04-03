#include "ds/tests/test_array.h"

/**
 * @brief Test the creation of an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_create(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    
    array_result = basec_array_create(&array, sizeof(u8), 10);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_create(NULL, sizeof(u8), 10);
    if (array_result == BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Creating array with NULL pointer succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_create(&array, 0, 10);
    if (array_result == BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Creating array with zero size succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_create(&array, sizeof(u8), 0);
    if (array_result == BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Creating array with zero capacity succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test appending an element to an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_append(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    
    array_result = basec_array_create(&array, sizeof(u8), 10);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->length != 0) {
        (void)strncpy(
            fail_message,
            "Array length is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->capacity != 10) {
        (void)strncpy(
            fail_message,
            "Array capacity is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    for (u8 i = 0; i < 15; i++) {
        array_result = basec_array_append(array, &i);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to append element to array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    if (array->length != 15) {
        (void)strncpy(
            fail_message,
            "Array length is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->capacity != 20) {
        (void)strncpy(
            fail_message,
            "Array did not grow as expected",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    for (u8 i = 0; i < array->length; i++) {
        u8 element = 0;

        array_result = basec_array_get(array, i, &element);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to get element from array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }

        if (element != i) {
            (void)strncpy(
                fail_message,
                "Element from array is not the expected value",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }
    
    array_result = basec_array_append(array, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Appending NULL element succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    for (u8 i = 0; i < 5; i++) {
        array_result = basec_array_append(array, &i);
        if (array_result == BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Appending element to destroyed array succeeded, expected failure",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    return true;
}

/**
 * @brief Test pushing an element to an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_push(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    
    array_result = basec_array_create(&array, sizeof(u8), 10);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->length != 0) {
        (void)strncpy(
            fail_message,
            "Array length is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->capacity != 10) {
        (void)strncpy(
            fail_message,
            "Array capacity is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    for (u8 i = 0; i < 15; i++) {
        array_result = basec_array_push(array, &i);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to push element to array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    if (array->length != 15) {
        (void)strncpy(
            fail_message,
            "Array length is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->capacity != 20) {
        (void)strncpy(
            fail_message,
            "Array did not grow as expected",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    for (u8 i = 0; i < array->length; i++) {
        u8 element = 0;

        array_result = basec_array_get(array, i, &element);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to get element from array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }

        if (element != i) {
            (void)strncpy(
                fail_message,
                "Element from array is not the expected value",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }
    
    array_result = basec_array_push(array, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Pushing NULL element succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    for (u8 i = 0; i < 5; i++) {
        array_result = basec_array_push(array, &i);
        if (array_result == BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Pushing element to destroyed array succeeded, expected failure",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    return true;
}

/**
 * @brief Test popping an element from an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_pop(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    u8               element_out   = 0;

    array_result = basec_array_create(&array, sizeof(u8), 5);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    for (u8 i = 0; i < 5; i++) {
        array_result = basec_array_push(array, &i);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to push element to array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    for (i8 i = array->length - 1; i >= 0; i--) {
        array_result = basec_array_pop(array, &element_out);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to pop element from array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }

        if (element_out != i) {
            (void)strncpy(
                fail_message,
                "Popped element is not the expected value",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    array_result = basec_array_pop(array, &element_out);
    if (array_result != BASEC_ARRAY_EMPTY) {
        (void)strncpy(
            fail_message,
            "Popping from an empty array succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_pop(array, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Popping from array with NULL pointer succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_pop(array, &element_out);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Popping from destroyed array succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test getting an element from an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_get(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    u8               element_out   = 0;

    array_result = basec_array_create(&array, sizeof(u8), 5);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    for (u8 i = 0; i < 5; i++) {
        array_result = basec_array_append(array, &i);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to append element to array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    for (u8 i = 0; i < 5; i++) {
        array_result = basec_array_get(array, i, &element_out);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to get element from array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }

        if (element_out != i) {
            (void)strncpy(
                fail_message,
                "Retrieved element is not the expected value",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    array_result = basec_array_get(array, 5, &element_out);
    if (array_result != BASEC_ARRAY_OUT_OF_BOUNDS) {
        (void)strncpy(
            fail_message,
            "Getting element at out of bounds index succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_get(array, 0, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting element with NULL pointer succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_get(array, 0, &element_out);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Getting from destroyed array succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test setting an element in an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_set(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    u8               element      = 0;

    array_result = basec_array_create(&array, sizeof(u8), 5);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->length != 0) {
        (void)strncpy(
            fail_message,
            "Array length is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->capacity != 5) {
        (void)strncpy(
            fail_message,
            "Array capacity is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    for (u8 i = 0; i < 5; i++) {
        array_result = basec_array_append(array, &element);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to append element to array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }
    
    if (array->length != 5) {
        (void)strncpy(
            fail_message,
            "Array length is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (array->capacity != 5) {
        (void)strncpy(
            fail_message,
            "Array capacity is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    for (u8 i = 0; i < array->length; i++) {
        array_result = basec_array_set(array, i, &i);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to set element in array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }
    
    for (u8 i = 0; i < array->length; i++) {
        array_result = basec_array_get(array, i, &element);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to get element from array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
        
        if (element != i) {
            (void)strncpy(
                fail_message,
                "Retrieved element is not the expected value",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    array_result = basec_array_set(array, 5, &element);
    if (array_result != BASEC_ARRAY_OUT_OF_BOUNDS) {
        (void)strncpy(
            fail_message,
            "Setting element at out of bounds index succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_set(array, 0, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Setting element with NULL pointer succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_set(array, 0, &element);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Setting element in destroyed array succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test checking if an array contains an element
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_contains(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    u8               element      = 42;
    bool             contains_out = false;

    array_result = basec_array_create(&array, sizeof(u8), 10);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_contains(array, &element, &contains_out);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Contains check for element failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (contains_out) {
        (void)strncpy(
            fail_message,
            "Contains check for non-existent element returned true",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_append(array, &element);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to append element to array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_contains(array, &element, &contains_out);
    if (array_result != BASEC_ARRAY_SUCCESS || !contains_out) {
        (void)strncpy(
            fail_message,
            "Contains check for existing element failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (!contains_out) {
        (void)strncpy(
            fail_message,
            "Contains check for existing element returned false",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_contains(array, NULL, &contains_out);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Contains check with NULL element succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_contains(array, &element, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Contains check with NULL contains_out succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_contains(array, &element, &contains_out);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Contains check with destroyed array succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test finding an element in an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_find(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    u8               element      = 42;
    u64              index_out    = 0;
    u8               ne_element   = 99;

    array_result = basec_array_create(&array, sizeof(u8), 10);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find(array, &element, &index_out);
    if (array_result != BASEC_ARRAY_NOT_FOUND) {
        (void)strncpy(
            fail_message,
            "Finding non-existent element returned success",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_append(array, &element);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to append element to array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_find(array, &element, &index_out);
    if (array_result != BASEC_ARRAY_SUCCESS || index_out != 0) {
        (void)strncpy(
            fail_message,
            "Failed to find existing element in array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    if (index_out != 0) {
        (void)strncpy(
            fail_message,
            "Index of existing element is not the expected value",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_find(array, &ne_element, &index_out);
    if (array_result != BASEC_ARRAY_NOT_FOUND) {
        (void)strncpy(
            fail_message,
            "Finding a non-existing element succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find(array, NULL, &index_out);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding with NULL element succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_find(array, &ne_element, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding with NULL index_out succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array after find test",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find(array, &element, &index_out);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding in destroyed array succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test finding all occurrences of an element in an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_find_all(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    u8 elements[]                 = {1, 2, 3, 2, 4};
    u8 search_element             = 2;
    u8 ne_element                 = 99;
    BasecArray*      indices      = NULL;

    array_result = basec_array_create(&array, sizeof(u8), 5);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array for find_all test",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    for (size_t i = 0; i < array->capacity; i++) {
        array_result = basec_array_append(array, &elements[i]);
        if (array_result != BASEC_ARRAY_SUCCESS) {
            (void)strncpy(
                fail_message,
                "Failed to append element to array",
                BASEC_TEST_FAIL_MESSAGE_MAX_LEN
            );
            return false;
        }
    }

    array_result = basec_array_find_all(array, &search_element, &indices);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to find all occurrences of element",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (indices->length != 2) {
        (void)strncpy(
            fail_message,
            "Incorrect number of occurrences found",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (((u64*)indices->data)[0] != 1 || ((u64*)indices->data)[1] != 3) {
        (void)strncpy(
            fail_message,
            "Found indices are incorrect",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find_all(array, &ne_element, &indices);
    if (array_result != BASEC_ARRAY_NOT_FOUND) {
        (void)strncpy(
            fail_message,
            "Finding non-existent element succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find_all(array, &search_element, &array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Finding all elements in place failed",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (array->length != 2) {
        (void)strncpy(
            fail_message,
            "Incorrect number of occurrences found",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (((u64*)array->data)[0] != 1 || ((u64*)array->data)[1] != 3) {
        (void)strncpy(
            fail_message,
            "Found indices are incorrect",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find_all(array, NULL, &array);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding all elements with NULL element succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find_all(array, &search_element, NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding all elements with NULL indices succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array after find_all test",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_find_all(array, &search_element, &indices);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Finding all elements in destroyed array succeeded",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

/**
 * @brief Test the destruction of an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
bool test_array_destroy(c_str fail_message) {
    BasecArrayResult array_result = BASEC_ARRAY_SUCCESS;
    BasecArray*      array        = NULL;
    
    array_result = basec_array_create(&array, sizeof(u8), 10);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to create array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_SUCCESS) {
        (void)strncpy(
            fail_message,
            "Failed to destroy array",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    array_result = basec_array_destroy(&array);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Double destroying array succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    
    array_result = basec_array_destroy(NULL);
    if (array_result != BASEC_ARRAY_NULL_POINTER) {
        (void)strncpy(
            fail_message,
            "Destroying NULL array succeeded, expected failure",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }
    return true;
}

/**
 * @brief Test the destruction of an array
 * @param fail_message The message to display if the test fails
 * @return The result of the test
 */
BasecTestResult test_array_add_tests(BasecTestSuite* test_suite) {
    BasecTestResult  test_result   = BASEC_TEST_SUCCESS;
    BasecTest*       create_test   = NULL;
    BasecTest*       append_test   = NULL;
    BasecTest*       push_test     = NULL;
    BasecTest*       pop_test      = NULL;
    BasecTest*       get_test      = NULL;
    BasecTest*       set_test      = NULL;
    BasecTest*       contains_test = NULL;
    BasecTest*       find_test     = NULL;
    BasecTest*       find_all_test = NULL;
    BasecTest*       destroy_test  = NULL;
    BasecTestModule* array_module  = NULL;

    test_result = basec_test_create(
        &create_test,
        "test_array_create",
        "Test the creation of an array",
        &test_array_create
    );
    if (test_result != BASEC_TEST_SUCCESS) return test_result;
    
    test_result = basec_test_create(
        &append_test,
        "test_array_append",
        "Test the appending of an element to an array",
        &test_array_append
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &push_test,
        "test_array_push",
        "Test the pushing of an element to an array",
        &test_array_push
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &pop_test,
        "test_array_pop",
        "Test the popping of an element from an array",
        &test_array_pop
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &get_test,
        "test_array_get",
        "Test the getting of an element from an array",
        &test_array_get
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &set_test,
        "test_array_set",
        "Test the setting of an element in an array",
        &test_array_set
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &contains_test,
        "test_array_contains",
        "Test the checking of an element in an array",
        &test_array_contains
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &find_test,
        "test_array_find",
        "Test the finding of an element in an array",
        &test_array_find
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &find_all_test,
        "test_array_find_all",
        "Test the finding of all occurrences of an element in an array",
        &test_array_find_all
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        return test_result;
    }
    
    test_result = basec_test_create(
        &destroy_test,
        "test_array_destroy",
        "Test the destruction of an array",
        &test_array_destroy
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        return test_result;
    }

    test_result = basec_test_module_create(
        &array_module,
        "Array"
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        return test_result;
    }

    test_result = basec_test_module_add_test(array_module, create_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&create_test);
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, append_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&append_test);
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, push_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&push_test);
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, pop_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&pop_test);
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, get_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&get_test);
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, set_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&set_test);
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, contains_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&contains_test);
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, find_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&find_test);
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_module_add_test(array_module, find_all_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&find_all_test);
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }

    test_result = basec_test_module_add_test(array_module, destroy_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&destroy_test);
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }
    
    test_result = basec_test_suite_add_module(test_suite, array_module);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_module_destroy(&array_module);
        return test_result;
    }

    return BASEC_TEST_SUCCESS;
}