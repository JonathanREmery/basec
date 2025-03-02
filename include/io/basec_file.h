/**
 * @file basec_file.h
 * @brief Header file for file operations
 */

#ifndef BASEC_FILE_H
#define BASEC_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief File modes
 */
#define FILE_MODE_READ "r"
#define FILE_MODE_WRITE "w"
#define FILE_MODE_APPEND "a"

/**
 * @brief File type
 */
typedef struct {
    char* path; //< Path to the file
    char* mode; //< Mode to open the file in
    FILE* file; //< File handle
} File;

/**
 * @brief Result of a file operation
 */
typedef enum {
    FILE_SUCCESS,              //< Success
    FILE_ERROR_NULL_POINTER,   //< Null pointer
    FILE_ERROR_INVALID_MODE,   //< Invalid mode
    FILE_ERROR_MALLOC,         //< Memory allocation failed
    FILE_ERROR_STRDUP,         //< Strdup failed
    FILE_ERROR_OPEN,           //< File could not be opened
    FILE_ERROR_DOES_NOT_EXIST, //< File does not exist
    FILE_ERROR_ALREADY_EXISTS, //< File already exists
    FILE_ERROR_CLOSE,          //< File could not be closed
    FILE_ERROR_REMOVE          //< File could not be removed
} FileResult;

/**
 * @brief Convert a FileResult to a string
 * 
 * @param result FileResult to convert
 * @return       String representation of the FileResult
 */
const char* file_result_to_string(FileResult result);

/**
 * @brief Check if a file exists
 * 
 * @param path       Path to the file
 * @param exists_out Output exists
 * @return           Result of the operation
 */
FileResult file_exists(const char* path, bool* exists_out);

/**
 * @brief Check if a mode is valid
 * 
 * @param mode      Mode to check
 * @param valid_out Output valid
 * @return          Result of the operation
 */
FileResult file_valid_mode(const char* mode, bool* valid_out);

/**
 * @brief Create a File struct
 * 
 * @param path     Path to the file
 * @param mode     Mode to open the file in
 * @param file_out File to be created
 * @return         Result of the file operation
 */
FileResult file_create(const char* path, const char* mode, File** file_out);

/**
 * @brief Open a File struct
 * 
 * @param path     Path to the file
 * @param mode     Mode to open the file in
 * @param file_out File to be opened
 * @return         Result of the file operation
 */
FileResult file_open(const char* path, const char* mode, File** file_out);

/**
 * @brief Remove a file
 * 
 * @param path Path to the file
 * @return     Result of the file operation
 */
FileResult file_remove(const char* path);

/**
 * @brief Destroy a File struct
 * 
 * @param file_ptr File to be destroyed
 * @return         Result of the file operation
 */
FileResult file_destroy(File** file_ptr);

#endif