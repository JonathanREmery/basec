#include <stdio.h>
#include <stdlib.h>

#include "basec_string.h"

int main(void) {
    BasecString* str = basec_string_create("Hello, World!", 128);
    printf("%s\n", str->data);
    basec_string_destroy(str);
    return 0;
}