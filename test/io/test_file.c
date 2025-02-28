/**
 * @file test_file.c
 * @brief Test implementation for the File type and functions
 */

#include "io/basec_file.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Test the file_create function
 */
void test_file_create() {
    printf("  Testing file_create...\n");

    // Test valid file creation
    File* file_valid = NULL;
    FileResult result_create_valid = file_create("test.txt", FILE_MODE_WRITE, &file_valid);
    assert(result_create_valid == FILE_SUCCESS);
    assert(file_valid != NULL);
    assert(file_valid->file != NULL);
    assert(strcmp(file_valid->path, "test.txt") == 0);
    assert(strcmp(file_valid->mode, FILE_MODE_WRITE) == 0);

    // Test NULL path
    File* file_null_path = NULL;
    FileResult result_null_path = file_create(NULL, FILE_MODE_WRITE, &file_null_path);
    assert(result_null_path == FILE_ERROR_NULL_POINTER);
    assert(file_null_path == NULL);

    // Test NULL mode
    File* file_null_mode = NULL;
    FileResult result_null_mode = file_create("test.txt", NULL, &file_null_mode);
    assert(result_null_mode == FILE_ERROR_NULL_POINTER);
    assert(file_null_mode == NULL);

    // Test NULL output
    FileResult result_null_out = file_create("test.txt", FILE_MODE_WRITE, NULL);
    assert(result_null_out == FILE_ERROR_NULL_POINTER);

    // Test invalid mode
    File* file_invalid_mode = NULL;
    FileResult result_invalid_mode = file_create("test.txt", "invalid", &file_invalid_mode);
    assert(result_invalid_mode == FILE_ERROR_OPEN);
    assert(file_invalid_mode == NULL);

    // Cleanup
    file_destroy(&file_valid);
}

/**
 * @brief Test the file_open function
 */
void test_file_open() {
    printf("  Testing file_open...\n");

    // Test valid file opening
    File* file_valid = NULL;
    FileResult result_open_valid = file_open("test.txt", FILE_MODE_WRITE, &file_valid);
    assert(result_open_valid == FILE_SUCCESS);
    assert(file_valid != NULL);
    assert(file_valid->file != NULL);
    assert(strcmp(file_valid->path, "test.txt") == 0);
    assert(strcmp(file_valid->mode, FILE_MODE_WRITE) == 0);

    // Test opening non-existent file in read mode (assuming it fails if file doesn't exist)
    File* file_read_nonexistent = NULL;
    FileResult result_read_nonexistent = file_open("nonexistent.txt", FILE_MODE_READ, &file_read_nonexistent);
    assert(result_read_nonexistent == FILE_ERROR_OPEN);
    assert(file_read_nonexistent == NULL);

    // Test NULL path
    File* file_null_path = NULL;
    FileResult result_null_path = file_open(NULL, FILE_MODE_WRITE, &file_null_path);
    assert(result_null_path == FILE_ERROR_NULL_POINTER);
    assert(file_null_path == NULL);

    // Test NULL mode
    File* file_null_mode = NULL;
    FileResult result_null_mode = file_open("test.txt", NULL, &file_null_mode);
    assert(result_null_mode == FILE_ERROR_NULL_POINTER);
    assert(file_null_mode == NULL);

    // Test NULL output
    FileResult result_null_out = file_open("test.txt", FILE_MODE_WRITE, NULL);
    assert(result_null_out == FILE_ERROR_NULL_POINTER);

    // Cleanup
    file_destroy(&file_valid);
}

/**
 * @brief Test the file_destroy function
 */
void test_file_destroy() {
    printf("  Testing file_destroy...\n");

    // Test destroying a valid file
    File* file_valid = NULL;
    FileResult result_create = file_create("test.txt", FILE_MODE_WRITE, &file_valid);
    assert(result_create == FILE_SUCCESS);
    FileResult result_destroy = file_destroy(&file_valid);
    assert(result_destroy == FILE_SUCCESS);
    assert(file_valid == NULL);

    // Test NULL pointer
    FileResult result_null = file_destroy(NULL);
    assert(result_null == FILE_ERROR_NULL_POINTER);

    // Test double destroy
    File* file_double = NULL;
    FileResult result_create_double = file_create("test.txt", FILE_MODE_WRITE, &file_double);
    assert(result_create_double == FILE_SUCCESS);
    FileResult result_destroy_double = file_destroy(&file_double);
    assert(result_destroy_double == FILE_SUCCESS);
    FileResult result_destroy_again = file_destroy(&file_double);
    assert(result_destroy_again == FILE_ERROR_NULL_POINTER);
}

int main() {
    printf("[basec_file] Running tests...\n");

    // Run all tests
    test_file_create();
    test_file_open();
    test_file_destroy();

    printf("[basec_file] All tests passed!\n");

    return 0;
}
