#include "basec_string.h"

BasecString* basec_string_create(const char* str, size_t capacity) {
    if (str == NULL || capacity <= 0) return NULL;

    BasecString* string = (BasecString*)malloc(sizeof(BasecString));
    if (string == NULL) {
        (void)printf("[Error] Memory allocation for the basec string failed\n");
        exit(1);
    }

    string->data = (char*)malloc(capacity);
    if (string->data == NULL) {
        (void)printf("[Error] Memory allocation for the basec string data failed\n");
        exit(1);
    }
    (void)strncpy(string->data, str, capacity);

    string->length = 0;
    string->capacity = capacity;

    return string;
}

void basec_string_destroy(BasecString* string) {
    free(string->data);
    free(string);
}