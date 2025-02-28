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
 * @brief Result of a file operation
 */
typedef enum {
    FILE_SUCCESS,               //< Success
    FILE_ERROR_NULL_POINTER,    //< Null pointer
    FILE_ERROR_MALLOC,          //< Memory allocation failed
    FILE_ERROR_OPEN,            //< File could not be opened
    FILE_ERROR_DOES_NOT_EXIST,  //< File does not exist
    FILE_ERROR_ALREADY_EXISTS,  //< File already exists
    FILE_ERROR_CLOSE,           //< File could not be closed
    FILE_ERROR_REMOVE           //< File could not be removed
} FileResult;

/**
 * @brief File type
 */
typedef struct {
    char* path; //< Path to the file
    char* mode; //< Mode to open the file in
    FILE* file; //< File handle
} File;

/**
 * @brief Check if a file exists
 * 
 * @param path The path to the file
 * @param exists_out Pointer to store the result (true if exists, false otherwise)
 * @return The result of the operation
 */
FileResult file_exists(const char* path, bool* exists_out);

/**
 * @brief Create a File struct
 * 
 * @param path The path to the file
 * @param mode The mode to open the file in
 * @param file_out The file to be created
 * @return The result of the file operation
 */
FileResult file_create(const char* path, const char* mode, File** file_out);

/**
 * @brief Open a File struct
 * 
 * @param path The path to the file
 * @param mode The mode to open the file in
 * @param file_out The file to be opened
 * @return The result of the file operation
 */
FileResult file_open(const char* path, const char* mode, File** file_out);

/**
 * @brief Remove a file
 * 
 * @param path The path to the file
 * @return The result of the file operation
 */
FileResult file_remove(const char* path);

/**
 * @brief Destroy a File struct
 * 
 * @param file_ptr The file to be destroyed
 * @return The result of the file operation
 */
FileResult file_destroy(File** file_ptr);

#endif