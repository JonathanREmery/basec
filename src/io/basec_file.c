/**
 * @file basec_file.c
 * @brief Implementation of file operations
 */

#include "io/basec_file.h"

/**
 * @brief Check if a file exists
 * 
 * @param path The path to the file
 * @param exists_out Pointer to store the result (true if exists, false otherwise)
 * @return The result of the operation
 */
FileResult file_exists(const char* path, bool* exists_out) {
    // Check for NULL pointers
    if (path == NULL || exists_out == NULL) {
        return FILE_ERROR_NULL_POINTER;
    }
    
    // Try to open the file in read mode
    FILE* file = fopen(path, "r");
    
    // Check if the file was opened successfully
    if (file != NULL) {
        // File exists, close it
        fclose(file);
        *exists_out = true;
    } else {
        // File does not exist
        *exists_out = false;
    }
    
    // Return success
    return FILE_SUCCESS;
}

/**
 * @brief Create a File struct
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

    // Check if the file already exists
    bool exists;
    FileResult exists_result = file_exists(path, &exists);
    if (exists_result != FILE_SUCCESS) {
        return exists_result;
    }

    // If the file exists, return an error
    if (exists) {
        return FILE_ERROR_ALREADY_EXISTS;
    }

    // Allocate memory for the File struct
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

    // Copy the path
    file->path = strdup(path);
    if (file->path == NULL) {
        free(file);
        return FILE_ERROR_MALLOC;
    }

    // Copy the mode
    file->mode = strdup(mode);
    if (file->mode == NULL) {
        free(file);
        return FILE_ERROR_MALLOC;
    }

    // Set the file handle
    *file_out = file;

    // Return success
    return FILE_SUCCESS;
}

/**
 * @brief Open a File struct
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

    // Check if the file already exists
    bool exists;
    FileResult exists_result = file_exists(path, &exists);
    if (exists_result != FILE_SUCCESS) {
        return exists_result;
    }

    // If the file does not exist, return an error
    if (!exists) {
        return FILE_ERROR_DOES_NOT_EXIST;
    }

    // Allocate memory for the File struct
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

    // Copy the path
    file->path = strdup(path);
    if (file->path == NULL) {
        free(file);
        return FILE_ERROR_MALLOC;
    }

    // Copy the mode
    file->mode = strdup(mode);
    if (file->mode == NULL) {
        free(file);
        return FILE_ERROR_MALLOC;
    }

    // Set the file handle
    *file_out = file;

    // Return success
    return FILE_SUCCESS;
}

/**
 * @brief Remove a file
 * 
 * @param path The path to the file
 * @return The result of the file operation
 */
FileResult file_remove(const char* path) {
    // Check for NULL pointer
    if (path == NULL) {
        return FILE_ERROR_NULL_POINTER;
    }

    // Remove the file
    int remove_result = remove(path);
    if (remove_result != 0) {
        return FILE_ERROR_REMOVE;
    }

    // Return success
    return FILE_SUCCESS;
}

/**
 * @brief Destroy a File struct
 * 
 * @param file_ptr The File struct to be destroyed
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
