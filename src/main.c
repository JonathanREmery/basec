#include <stdio.h>
#include <stdlib.h>

#include "ds/basec_string.h"

int main(void) {
    BasecString* string = NULL;
    (void)basec_string_create(&string, ", ", 128);

    c_str str;
    u64 length;
    u64 capacity;
    (void)basec_string_c_str(&string, &str);
    (void)basec_string_length(&string, &length);
    (void)basec_string_capacity(&string, &capacity);

    printf("string: %s\n", str);
    printf("-> length: %zu\n", length);
    printf("-> capacity: %zu\n\n", capacity);
    
    (void)basec_string_prepend(&string, "Hello");
    (void)basec_string_c_str(&string, &str);
    (void)basec_string_length(&string, &length);
    (void)basec_string_capacity(&string, &capacity);

    printf("string: %s\n", str);
    printf("-> length: %zu\n", length);
    printf("-> capacity: %zu\n\n", capacity);

    (void)basec_string_append(&string, "World!");
    (void)basec_string_c_str(&string, &str);
    (void)basec_string_length(&string, &length);
    (void)basec_string_capacity(&string, &capacity);

    printf("string: %s\n", str);
    printf("-> length: %zu\n", length);
    printf("-> capacity: %zu\n", capacity);

    (void)basec_string_destroy(&string);
    return 0;
}