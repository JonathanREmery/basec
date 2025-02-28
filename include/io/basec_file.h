/**
 * @file basec_file.h
 * @brief Header file for file operations
 */

#ifndef BASEC_FILE_H
#define BASEC_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief File modes
 */
#define FILE_MODE_READ "r"
#define FILE_MODE_WRITE "w"
#define FILE_MODE_APPEND "a"

/**
 * @brief Result of a file operation
 */
typedef enum {
    FILE_SUCCESS,
    FILE_ERROR_NULL_POINTER,
    FILE_ERROR_MALLOC,
    FILE_ERROR_OPEN,
    FILE_ERROR_CLOSE
} FileResult;

/**
 * @brief File type
 */
typedef struct {
    char* path;
    char* mode;
    FILE* file;
} File;

/**
 * @brief Create a file handle
 * 
 * @param path The path to the file
 * @param mode The mode to open the file in
 * @param file_out The file to be created
 * @return The result of the file operation
 */
FileResult file_create(const char* path, const char* mode, File** file_out);

/**
 * @brief Open a file
 * 
 * @param path The path to the file
 * @param mode The mode to open the file in
 * @param file_out The file to be opened
 * @return The result of the file operation
 */
FileResult file_open(const char* path, const char* mode, File** file_out);

/**
 * @brief Destroy a file
 * 
 * @param file_ptr The file to be destroyed
 * @return The result of the file operation
 */
FileResult file_destroy(File** file_ptr);

#endif