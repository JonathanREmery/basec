# basec

basec is a C base layer with a focus on simplicity, performance, and safety.

## Project Structure

```bash
basec
├── bin                    -- Binaries
├── bootstrap.sh           -- Build Bootstrap
├── include                -- Header Files
│   ├── basec_types.h        -- Common Types
│   ├── ds                   -- Data Structures
│   └── util                 -- Utilities
└── src                    -- Source Files
    ├── ds                   -- Data Structures
    ├── main.c               -- Example Code
    └── util                 -- Utilities
```

## Build System

basec has it's own build system that supports automatic rebuilding. All you 
need to do is include `include/util/basec_build.h` and configure the system for
your project. The recommended way to do this is write a static build function
in your main C file. Then simply call it at the beginning of `main.c`. Any time
you change your project's code, basec's build system will detect this and
automatically rebuild, then replace itself with the latest binary. This means
you simply run your program and don't have to worry about compiling.

```c
#include "util/basec_build.h"

static void _build(void) {
    BuildSystem* build_system = NULL;
    BuildTarget  basec        = {
        .name = "basec",
        .sources = {
            "src/main.c",
            "src/util/basec_build.c",
            "src/ds/basec_string.c",
            "src/ds/basec_array.c",
        },
        .includes = {
            "include",
        }
    };

    basec_build_handle_result(
        basec_build_system_create(&build_system)
    );

    basec_build_handle_result(
        basec_build_system_add_target(build_system, basec)
    );

    basec_build_handle_result(
        basec_build_system_build(build_system)
    );

    basec_build_handle_result(
        basec_build_system_destroy(&build_system)
    );
}

int main(void) {
    _build();

    // rest of the code
}
```

## Results

Every function in basec returns some type of result that the caller can choose
how to handle. In the Build System example you can see this
`basec_build_handle_result` function. This is not required, you can choose to 
ignore results, handle them yourself, or use the built in handler functions.
In most cases it would make sense to handle them yourself, as the built in
handler functions print a message and quit on errors, which may not be the
intended behavior.

```c
// Ignore result
(void)basec_build_system_create(&build_system);

// Handle yourself
BasecBuildResult result = basec_build_system_create(&build_system);
if (result != BASEC_BUILD_SUCCESS) {
    // do something
}

// Use built in handler
basec_build_handle_result(basec_build_system_create(&build_system));
```

## Strings

basec Strings are built on top of 'C strings', which are arrays of chars. You
can always access the underlying data with `string->data` or by using the
`basec_string_c_str` function. basec Strings are dynamic, meaning they will
resize themselves as needed. Many of the common string operations you're used
to in higher level languages are supported. Such as `prepend`, `append`,
`contains`, `find`, `find_all`, `replace`, and `split`.

```c
BasecStringResult string_result = BASEC_STRING_SUCCESS;
BasecString*      string        = NULL;

string_result = basec_string_create(&string, "Hello", 10);
basec_string_handle_result(string_result);

(void)printf("%s\n", string->data);
// Hello

string_result = basec_string_append(string, ", World!");
basec_string_handle_result(string_result);

(void)printf("%s\n", string->data);
// Hello, World!

/*
* Operations which take an output pointer can be used in place by simply
* passing the same pointer
*/
string_result = basec_string_replace(string, "Hello", "Goodbye", &string);
basec_string_handle_result(string_result);

(void)printf("%s\n", string->data);
// Goodbye, World!
```

## Arrays

basec Arrays are also dynamic. They are homogenous, meaning any data type can
be stored, but every element must be the same type. Some supported operations 
are `append/push`, `pop`, `get`, `set`, `contains`, `find`, and `find_all`.

```c
BasecArray* array    = NULL;
u64         element  = 3;
bool        contains = false;
u64         index    = 0;

basec_array_handle_result(
    basec_array_create(&array, sizeof(u64), 10)
);

for (u64 i = 1; i <= 5; i++) {
    basec_array_handle_result(
        basec_array_append(array, &i)
    );
}

(void)printf("array\n");
for (u64 i = 0; i < array->length; i++) {
    u64 element = 0;
    basec_array_handle_result(
        basec_array_get(array, i, (void*)&element)
    );
    (void)printf("-> %lu\n", element);
}
// array
// -> 1
// -> 2
// -> 3
// -> 4
// -> 5

basec_array_handle_result(
    basec_array_contains(array, (void*)&element, &contains)
);

(void)printf("contains(%lu): ", element);
if (contains) {
    (void)printf("true\n");
} else {
    (void)printf("false\n");
}
// contains(3): true

basec_array_handle_result(
    basec_array_find(array, (void*)&element, &index)
);

(void)printf("find(%lu): %lu", element, index);
// find(3): 2
```
