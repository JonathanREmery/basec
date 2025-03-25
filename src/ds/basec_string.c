#include "ds/basec_string.h"

// Growth factor for the string
static const u8 _GROWTH_FACTOR = 2;

/**
 * @brief Create a new string
 * @param str The string to create
 * @param capacity The capacity of the string
 * @return A pointer to the new string
 */
BasecString* basec_string_create(const c_str str, u64 capacity) {
    if (str == NULL || capacity <= 0) return NULL;

    BasecString* string = (BasecString*)malloc(sizeof(BasecString));
    if (string == NULL) {
        (void)printf("[Error] Memory allocation for the basec string failed\n");
        exit(1);
    }

    string->length = strlen(str);
    if (string->length > capacity) capacity = string->length * _GROWTH_FACTOR;

    string->data = (c_str)malloc(capacity + 1);
    if (string->data == NULL) {
        (void)printf("[Error] Memory allocation for the basec string data failed\n");
        exit(1);
    }

    (void)strncpy(string->data, str, string->length);
    string->data[string->length + 1] = '\0';

    string->capacity = capacity;

    return string;
}

/**
 * @brief Get the string as a c_str
 * @param string The string to get
 * @return The string as a c_str
 */
c_str basec_string_c_str(BasecString* string) {
    if (string == NULL) return NULL;
    return string->data;
}

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend_str The string to prepend
 */
static void _basec_string_grow(BasecString* string, u64 new_capacity) {
    if (string == NULL || new_capacity <= 0) return;

    string->data = (char*)realloc(string->data, new_capacity * _GROWTH_FACTOR);
    if (string->data == NULL) {
        (void)printf("[Error] Memory allocation for the basec string data failed\n");
        exit(1);
    }

    string->capacity = new_capacity;
}

/**
 * @brief Prepend a string to the string
 * @param string The string to prepend to
 * @param prepend_str The string to prepend
 */
void basec_string_prepend(BasecString* string, const c_str prepend_str) {
    if (string == NULL || prepend_str == NULL) return;

    u64 prepend_len = strlen(prepend_str);
    u64 new_len = string->length + prepend_len;

    if (new_len > string->capacity) _basec_string_grow(string, new_len);
    
    (void)memmove(string->data + prepend_len, string->data, string->length);
    (void)memcpy(string->data, prepend_str, prepend_len);

    string->length = new_len;
}

/**
 * @brief Append a string to the string
 * @param string The string to append to
 * @param append_str The string to append
 */
void basec_string_append(BasecString* string, const c_str append_str) {
    if (string == NULL || append_str == NULL) return;

    u64 append_len = strlen(append_str);
    u64 new_len = string->length + append_len;

    if (new_len > string->capacity) _basec_string_grow(string, new_len);

    (void)strncpy(string->data + string->length, append_str, append_len);
    string->length = new_len;
    string->data[string->length + 1] = '\0';
}

/**
 * @brief Destroy a string
 * @param string The string to destroy
 */
void basec_string_destroy(BasecString* string) {
    if (string == NULL) return;

    free(string->data);
    free(string);
    string = NULL;
}