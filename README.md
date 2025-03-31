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
│   │   └── tests              -- Data Structure Tests
│   └── util                 -- Utilities
└── src                    -- Source Files
    ├── ds                   -- Data Structures
    ├── main.c               -- Example Code
    ├── test.c               -- Test Code
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
            // source files
        },
        .includes = {
            // include directories
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
BasecArray* array        = NULL;
u64         find_element = 3;
bool        contains     = false;
u64         index        = 0;

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
    basec_array_contains(array, (void*)&find_element, &contains)
);

(void)printf("contains(%lu): ", find_element);
if (contains) {
    (void)printf("true\n");
} else {
    (void)printf("false\n");
}
// contains(3): true

basec_array_handle_result(
    basec_array_find(array, (void*)&find_element, &index)
);

(void)printf("find(%lu): %lu", find_element, index);
// find(3): 2
```

## Test Suite

basec has a Test Suite that can be used to manage tests for different Modules.
The workflow is to create test functions that return a boolean value reflecting
the success or failure, and takes in a failure message. If the test fails it's
up to the test function to set the failure message. Then a Test can be created.
Tests are organized into TestModules. Which are run by the TestSuite. An 
example of this might look something like this.

```c
/* arithmetic.h */
i64 add(i64 x, i64 y);
i64 sub(i64 x, i64 y);

/* arithmetic.c */
i64 add(i64 x, i64 y) {
    return x + y;
}

i64 sub(i64 x, i64 y) {
    return x - y;
}

/* test_arithmetic.h */
bool            test_add(c_str fail_message);
bool            test_sub(c_str fail_message);
BasecTestResult test_arithmetic_add_tests(BasecTestSuite* test_suite);

/* test_arithmetic.c */
bool test_add(c_str fail_message) {
    if (add(5, 3) != 8) {
        (void)strncpy(
            fail_message,
            "add(5, 3) != 8",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (add(7, -1) != 6) {
        (void)strncpy(
            fail_message,
            "add(7, -1) != 6",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

bool test_sub(c_str fail_message) {
    if (sub(5, 3) != 2) {
        (void)strncpy(
            fail_message,
            "sub(5, 3) != 2",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    if (sub(7, -1) != 8) {
        (void)strncpy(
            fail_message,
            "sub(7, -1) != 8",
            BASEC_TEST_FAIL_MESSAGE_MAX_LEN
        );
        return false;
    }

    return true;
}

BasecTestResult test_arithmetic_add_tests(TestSuite* test_suite) {
    BasecTestResult  test_result = BASEC_TEST_SUCCESS;
    BasecTest*       add_test    = NULL;
    BasecTest*       sub_test    = NULL;
    BasecTestModule* test_module = NULL;

    test_result = basec_test_create(
        &add_test,
        "test_add",
        "Test the addition function",
        &test_add
    );
    if (test_result != BASEC_TEST_SUCCESS) return test_result;

    test_result = basec_test_create(
        &sub_test,
        "test_sub",
        "Test the subtraction function",
        &test_sub
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&add_test);
        return test_result;
    }
    
    test_result = basec_test_module_create(
        &test_module,
        "Arithmetic"
    );
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&add_test);
        (void)basec_test_destroy(&sub_test);
        return test_result;
    }

    test_result = basec_test_module_add_test(test_module, add_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&add_test);
        (void)basec_test_destroy(&sub_test);
        (void)basec_test_module_destroy(&test_module);
        return test_result;
    }

    test_result = basec_test_module_add_test(test_module, sub_test);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_destroy(&sub_test);
        (void)basec_test_module_destroy(&test_module);
        return test_result;
    }
    
    test_result = basec_test_suite_add_module(test_suite, test_module);
    if (test_result != BASEC_TEST_SUCCESS) {
        (void)basec_test_module_destroy(&test_module);
        return test_result;
    }

    return BASEC_TEST_SUCCESS;
}

/* test.c */
BasecTestSuite* test_suite = NULL;

basec_test_handle_result(basec_test_suite_create(&test_suite));

basec_test_handle_result(test_arithmetic_add_tests(test_suite));

basec_test_handle_result(basec_test_suite_run(test_suite));
basec_test_handle_result(basec_test_suite_print_results(test_suite));

basec_test_handle_result(basec_test_suite_destroy(&test_suite));
```
