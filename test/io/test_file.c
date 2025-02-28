/**
 * @file test_file.c
 * @brief Test implementation for the File type and functions
 */

#include "io/basec_file.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE_PATH "test.txt"

/**
 * @brief Test the file_exists function
 */
void test_file_exists() {
    printf("  Testing file_exists...\n");

    // Create a file manually
    FILE* setup_file = fopen(TEST_FILE_PATH, "w");
    assert(setup_file != NULL);
    fclose(setup_file);

    // Test with existing file
    bool exists;
    FileResult result_exists = file_exists(TEST_FILE_PATH, &exists);
    assert(result_exists == FILE_SUCCESS);
    assert(exists == true);

    // Cleanup file on disk
    remove(TEST_FILE_PATH);

    // Ensure non-existent file doesn't exist before testing
    remove("nonexistent.txt");

    // Test with non-existent file
    FileResult result_nonexistent = file_exists("nonexistent.txt", &exists);
    assert(result_nonexistent == FILE_SUCCESS);
    assert(exists == false);

    // Test NULL path
    FileResult result_null_path = file_exists(NULL, &exists);
    assert(result_null_path == FILE_ERROR_NULL_POINTER);

    // Test NULL output
    FileResult result_null_out = file_exists(TEST_FILE_PATH, NULL);
    assert(result_null_out == FILE_ERROR_NULL_POINTER);
}

/**
 * @brief Test the file_create function
 */
void test_file_create() {
    printf("  Testing file_create...\n");

    // Test valid file creation
    File* file_valid = NULL;
    FileResult result_create_valid = file_create(TEST_FILE_PATH, FILE_MODE_WRITE, &file_valid);
    assert(result_create_valid == FILE_SUCCESS);
    assert(file_valid != NULL);
    assert(file_valid->file != NULL);
    assert(strcmp(file_valid->path, TEST_FILE_PATH) == 0);
    assert(strcmp(file_valid->mode, FILE_MODE_WRITE) == 0);

    // Cleanup
    fclose(file_valid->file);
    free(file_valid->path);
    free(file_valid->mode);
    free(file_valid);
    remove(TEST_FILE_PATH);

    // Test creating an existing file
    FILE* setup_file = fopen(TEST_FILE_PATH, "w");
    assert(setup_file != NULL);
    fclose(setup_file);
    File* file_duplicate = NULL;
    FileResult result_duplicate = file_create(TEST_FILE_PATH, FILE_MODE_WRITE, &file_duplicate);
    assert(result_duplicate == FILE_ERROR_ALREADY_EXISTS);
    assert(file_duplicate == NULL);

    // Cleanup file on disk
    remove(TEST_FILE_PATH);

    // Test NULL path
    File* file_null_path = NULL;
    FileResult result_null_path = file_create(NULL, FILE_MODE_WRITE, &file_null_path);
    assert(result_null_path == FILE_ERROR_NULL_POINTER);
    assert(file_null_path == NULL);

    // Test NULL mode
    File* file_null_mode = NULL;
    FileResult result_null_mode = file_create(TEST_FILE_PATH, NULL, &file_null_mode);
    assert(result_null_mode == FILE_ERROR_NULL_POINTER);
    assert(file_null_mode == NULL);

    // Test NULL output
    FileResult result_null_out = file_create(TEST_FILE_PATH, FILE_MODE_WRITE, NULL);
    assert(result_null_out == FILE_ERROR_NULL_POINTER);

    // Test invalid mode
    File* file_invalid_mode = NULL;
    FileResult result_invalid_mode = file_create(TEST_FILE_PATH, "invalid", &file_invalid_mode);
    assert(result_invalid_mode == FILE_ERROR_OPEN);
    assert(file_invalid_mode == NULL);
}

/**
 * @brief Test the file_open function
 */
void test_file_open() {
    printf("  Testing file_open...\n");

    // Create a file manually
    FILE* setup_file = fopen(TEST_FILE_PATH, "w");
    assert(setup_file != NULL);
    fclose(setup_file);

    // Test valid file opening
    File* file_valid = NULL;
    FileResult result_open_valid = file_open(TEST_FILE_PATH, FILE_MODE_WRITE, &file_valid);
    assert(result_open_valid == FILE_SUCCESS);
    assert(file_valid != NULL);
    assert(file_valid->file != NULL);
    assert(strcmp(file_valid->path, TEST_FILE_PATH) == 0);
    assert(strcmp(file_valid->mode, FILE_MODE_WRITE) == 0);

    // Cleanup
    fclose(file_valid->file);
    free(file_valid->path);
    free(file_valid->mode);
    free(file_valid);
    remove(TEST_FILE_PATH);

    // Test opening non-existent file
    File* file_nonexistent = NULL;
    FileResult result_nonexistent = file_open("nonexistent.txt", FILE_MODE_READ, &file_nonexistent);
    assert(result_nonexistent == FILE_ERROR_DOES_NOT_EXIST);
    assert(file_nonexistent == NULL);

    // Test NULL path
    File* file_null_path = NULL;
    FileResult result_null_path = file_open(NULL, FILE_MODE_WRITE, &file_null_path);
    assert(result_null_path == FILE_ERROR_NULL_POINTER);
    assert(file_null_path == NULL);

    // Test NULL mode
    File* file_null_mode = NULL;
    FileResult result_null_mode = file_open(TEST_FILE_PATH, NULL, &file_null_mode);
    assert(result_null_mode == FILE_ERROR_NULL_POINTER);
    assert(file_null_mode == NULL);

    // Test NULL output
    FileResult result_null_out = file_open(TEST_FILE_PATH, FILE_MODE_WRITE, NULL);
    assert(result_null_out == FILE_ERROR_NULL_POINTER);
}

/**
 * @brief Test the file_remove function
 */
void test_file_remove() {
    printf("  Testing file_remove...\n");

    // Test removing an existing file
    FILE* setup_file = fopen(TEST_FILE_PATH, "w");
    assert(setup_file != NULL);
    fclose(setup_file);
    FileResult result_remove = file_remove(TEST_FILE_PATH);
    assert(result_remove == FILE_SUCCESS);

    // Test removing a non-existent file
    FileResult result_nonexistent = file_remove("nonexistent.txt");
    assert(result_nonexistent == FILE_ERROR_REMOVE);

    // Test NULL path
    FileResult result_null = file_remove(NULL);
    assert(result_null == FILE_ERROR_NULL_POINTER);
}

/**
 * @brief Test the file_destroy function
 */
void test_file_destroy() {
    printf("  Testing file_destroy...\n");

    // Test destroying a valid file
    File* file_valid = malloc(sizeof(File));
    assert(file_valid != NULL);
    file_valid->path = strdup(TEST_FILE_PATH);
    assert(file_valid->path != NULL);
    file_valid->mode = strdup(FILE_MODE_WRITE);
    assert(file_valid->mode != NULL);
    file_valid->file = fopen(TEST_FILE_PATH, FILE_MODE_WRITE);
    assert(file_valid->file != NULL);
    FileResult result_destroy = file_destroy(&file_valid);
    assert(result_destroy == FILE_SUCCESS);
    assert(file_valid == NULL);
    // Cleanup file on disk
    remove(TEST_FILE_PATH);

    // Test NULL pointer
    FileResult result_null = file_destroy(NULL);
    assert(result_null == FILE_ERROR_NULL_POINTER);

    // Test double destroy
    File* file_double = malloc(sizeof(File));
    assert(file_double != NULL);
    file_double->path = strdup(TEST_FILE_PATH);
    assert(file_double->path != NULL);
    file_double->mode = strdup(FILE_MODE_WRITE);
    assert(file_double->mode != NULL);
    file_double->file = fopen(TEST_FILE_PATH, FILE_MODE_WRITE);
    assert(file_double->file != NULL);
    FileResult result_destroy_double = file_destroy(&file_double);
    assert(result_destroy_double == FILE_SUCCESS);
    assert(file_double == NULL);
    FileResult result_destroy_again = file_destroy(&file_double);
    assert(result_destroy_again == FILE_ERROR_NULL_POINTER);

    // Cleanup file on disk
    remove(TEST_FILE_PATH);
}

int main() {
    printf("[basec_file] Running tests...\n");

    // Run all tests
    test_file_exists();
    test_file_create();
    test_file_open();
    test_file_remove();
    test_file_destroy();

    printf("[basec_file] All tests passed!\n");

    return 0;
}
