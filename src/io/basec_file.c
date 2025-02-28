/**
 * @file basec_file.c
 * @brief Implementation of file operations
 */

#include "io/basec_file.h"

/**
 * @brief Create a file handle
 * 
 * @param path The path to the file
 * @param mode The mode to open the file in
 * @param file_out The file to be created
 * @return The result of the file operation
 */
FileResult file_create(const char* path, const char* mode, File** file_out) {
    // Check for NULL pointers
    if (path == NULL || mode == NULL || file_out == NULL) {
        return FILE_ERROR_NULL_POINTER;
    }

    // Allocate memory for the file handle
    File* file = (File*)malloc(sizeof(File));
    if (file == NULL) {
        return FILE_ERROR_MALLOC;
    }

    // Open the file
    file->file = fopen(path, mode);
    if (file->file == NULL) {
        free(file);
        return FILE_ERROR_OPEN;
    }

    // Copy the path and mode
    file->path = strdup(path);
    file->mode = strdup(mode);

    // Set the file handle
    *file_out = file;

    // Return success
    return FILE_SUCCESS;
}

/**
 * @brief Open a file
 * 
 * @param path The path to the file
 * @param mode The mode to open the file in
 * @param file_out The file to be opened
 * @return The result of the file operation
 */
FileResult file_open(const char* path, const char* mode, File** file_out) {
    // Check for NULL pointers
    if (path == NULL || mode == NULL || file_out == NULL) {
        return FILE_ERROR_NULL_POINTER;
    }

    // Create the file handle
    return file_create(path, mode, file_out);
}

/**
 * @brief Destroy a file
 * 
 * @param file_ptr The file to be destroyed
 * @return The result of the file operation
 */
FileResult file_destroy(File** file_ptr) {
    // Check for NULL pointers
    if (file_ptr == NULL || *file_ptr == NULL) {
        return FILE_ERROR_NULL_POINTER;
    }

    // Close the file
    if ((*file_ptr)->file != NULL) {
        int close_result = fclose((*file_ptr)->file);
        if (close_result != 0) {
            return FILE_ERROR_CLOSE;
        }
    }

    // Free the memory allocated for the path
    if ((*file_ptr)->path != NULL) {
        free((*file_ptr)->path);
        (*file_ptr)->path = NULL;
    }

    // Free the memory allocated for the mode
    if ((*file_ptr)->mode != NULL) {
        free((*file_ptr)->mode);
        (*file_ptr)->mode = NULL;
    }

    // Free the memory allocated for the File struct
    free(*file_ptr);
    *file_ptr = NULL;

    // Return success
    return FILE_SUCCESS;
}
