/**
 * @file basec_file.c
 * @brief Implementation of file operations
 */

#include "io/basec_file.h"

/**
 * @brief Convert a FileResult to a string
 * 
 * @param result FileResult to convert
 * @return       String representation of the FileResult
 */
const char* file_result_to_string(FileResult result) {
    switch (result) {
        case FILE_SUCCESS:
            return "FILE_SUCCESS";              //< Success
        case FILE_ERROR_NULL_POINTER:
            return "FILE_ERROR_NULL_POINTER";   //< NULL pointer
        case FILE_ERROR_INVALID_MODE:
            return "FILE_ERROR_INVALID_MODE";   //< Invalid mode
        case FILE_ERROR_MALLOC:
            return "FILE_ERROR_MALLOC";         //< Memory allocation failed
        case FILE_ERROR_STRDUP:
            return "FILE_ERROR_STRDUP";         //< Strdup failed
        case FILE_ERROR_OPEN:
            return "FILE_ERROR_OPEN";           //< File could not be opened
        case FILE_ERROR_DOES_NOT_EXIST:
            return "FILE_ERROR_DOES_NOT_EXIST"; //< File does not exist
        case FILE_ERROR_ALREADY_EXISTS:
            return "FILE_ERROR_ALREADY_EXISTS"; //< File already exists
        case FILE_ERROR_CLOSE:
            return "FILE_ERROR_CLOSE";          //< File could not be closed
        case FILE_ERROR_REMOVE:
            return "FILE_ERROR_REMOVE";         //< File could not be removed
        default:
            return "UNKNOWN_FILE_RESULT";       //< Unknown file result
    }
}

/**
 * @brief Check if a file exists
 * 
 * @param path       Path to the file
 * @param exists_out Output exists
 * @return           Result of the operation
 */
FileResult file_exists(const char* path, bool* exists_out) {
    // Check for NULL pointers
    if (path == NULL || exists_out == NULL) return FILE_ERROR_NULL_POINTER;
    
    // Try to open the file in read mode
    FILE* file = fopen(path, "r");
    
    // Check if the file was opened successfully
    if (file != NULL) {
        // Close the file
        fclose(file);

        // Set the output exists to true
        *exists_out = true;
    } else {
        // Set the output exists to false
        *exists_out = false;
    }
    
    // Success
    return FILE_SUCCESS;
}

/**
 * @brief Check if a mode is valid
 * 
 * @param mode      Mode to check
 * @param valid_out Output valid
 * @return          Result of the operation
 */
FileResult file_valid_mode(const char* mode, bool* valid_out) {
    // Check for NULL pointers
    if (mode == NULL || valid_out == NULL) return FILE_ERROR_NULL_POINTER;

    // Set the output valid
    *valid_out = strcmp(mode, FILE_MODE_READ)   == 0 ||
                 strcmp(mode, FILE_MODE_WRITE)  == 0 ||
                 strcmp(mode, FILE_MODE_APPEND) == 0;

    // Check if the mode is valid
    if (!*valid_out) return FILE_ERROR_INVALID_MODE;

    // Success
    return FILE_SUCCESS;
}

/**
 * @brief Create a File struct
 * 
 * @param path     Path to the file
 * @param mode     Mode to open the file in
 * @param file_out File to be created
 * @return         Result of the file operation
 */
FileResult file_create(const char* path, const char* mode, File** file_out) {
    // Check for NULL pointers
    if (path == NULL || mode == NULL || file_out == NULL) {
        // NULL pointer
        return FILE_ERROR_NULL_POINTER;
    }

    // Check if the mode is valid
    bool valid;
    FileResult valid_result = file_valid_mode(mode, &valid);
    if (valid_result != FILE_SUCCESS) return valid_result;
    if (!valid) return FILE_ERROR_INVALID_MODE;

    // Check if the file exists
    bool exists;
    FileResult exists_result = file_exists(path, &exists);
    if (exists_result != FILE_SUCCESS) return exists_result;
    if (exists) return FILE_ERROR_ALREADY_EXISTS;

    // Allocate memory for the file struct
    File* file = (File*)malloc(sizeof(File));

    // Check if the allocation failed
    if (file == NULL) return FILE_ERROR_MALLOC;

    // Open the file
    file->file = fopen(path, mode);

    // Check if the file could not be opened
    if (file->file == NULL) {
        // Free the file struct
        free(file);

        // Open failed
        return FILE_ERROR_OPEN;
    }

    // Copy the path
    file->path = strdup(path);

    // Check if the path could not be copied
    if (file->path == NULL) {
        // Free the file struct
        free(file);

        // Strdup failed
        return FILE_ERROR_STRDUP;
    }

    // Copy the mode
    file->mode = strdup(mode);

    // Check if the mode could not be copied
    if (file->mode == NULL) {
        // Free the file struct
        free(file);

        // Strdup failed
        return FILE_ERROR_STRDUP;
    }

    // Set the file handle
    *file_out = file;

    // Success
    return FILE_SUCCESS;
}

/**
 * @brief Open a File struct
 * 
 * @param path     Path to the file
 * @param mode     Mode to open the file in
 * @param file_out File to be opened
 * @return         Result of the file operation
 */
FileResult file_open(const char* path, const char* mode, File** file_out) {
    // Check for NULL pointers
    if (path == NULL || mode == NULL || file_out == NULL) {
        // NULL pointer
        return FILE_ERROR_NULL_POINTER;
    }

    // Check if the mode is valid
    bool valid;
    FileResult valid_result = file_valid_mode(mode, &valid);
    if (valid_result != FILE_SUCCESS) return valid_result;
    if (!valid) return FILE_ERROR_INVALID_MODE;

    // Check if the file exists
    bool exists;
    FileResult exists_result = file_exists(path, &exists);
    if (exists_result != FILE_SUCCESS) return exists_result;
    if (!exists) return FILE_ERROR_DOES_NOT_EXIST;

    // Allocate memory for the File struct
    File* file = (File*)malloc(sizeof(File));

    // Check if the allocation failed
    if (file == NULL) return FILE_ERROR_MALLOC;
    
    // Open the file
    file->file = fopen(path, mode);

    // Check if the file could not be opened
    if (file->file == NULL) {
        // Free the file struct
        free(file);

        // Open failed
        return FILE_ERROR_OPEN;
    }

    // Copy the path
    file->path = strdup(path);

    // Check if the path could not be copied
    if (file->path == NULL) {
        // Free the file struct
        free(file);

        // Strdup failed
        return FILE_ERROR_STRDUP;
    }

    // Copy the mode
    file->mode = strdup(mode);

    // Check if the mode could not be copied
    if (file->mode == NULL) {
        // Free the file struct
        free(file);

        // Strdup failed
        return FILE_ERROR_STRDUP;
    }

    // Set the file handle
    *file_out = file;

    // Success
    return FILE_SUCCESS;
}

/**
 * @brief Remove a file
 * 
 * @param path Path to the file
 * @return     Result of the file operation
 */
FileResult file_remove(const char* path) {
    // Check for NULL pointer
    if (path == NULL) return FILE_ERROR_NULL_POINTER;

    // Remove the file
    int remove_result = remove(path);

    // Check if the file could not be removed
    if (remove_result != 0) return FILE_ERROR_REMOVE;

    // Success
    return FILE_SUCCESS;
}

/**
 * @brief Destroy a File struct
 * 
 * @param file_ptr File to be destroyed
 * @return         Result of the file operation
 */
FileResult file_destroy(File** file_ptr) {
    // Check for NULL pointers
    if (file_ptr == NULL || *file_ptr == NULL) return FILE_ERROR_NULL_POINTER;

    // Check if the file is open
    if ((*file_ptr)->file != NULL) {
        // Close the file
        int close_result = fclose((*file_ptr)->file);

        // Check if the file could not be closed
        if (close_result != 0) {
            // Close failed
            return FILE_ERROR_CLOSE;
        }
    }

    // Free the path if it exists
    if ((*file_ptr)->path != NULL) free((*file_ptr)->path);

    // Free the mode if it exists
    if ((*file_ptr)->mode != NULL) free((*file_ptr)->mode);

    // Free the file struct
    free(*file_ptr);

    // Set the file pointer to NULL
    *file_ptr = NULL;

    // Success
    return FILE_SUCCESS;
}
