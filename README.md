# basec - C Base Layer Library
**basec** is a lightweight C library providing foundational data structures and utilities, emphasizing memory safety, efficiency, and ease of use.

## Project Structure
```
basec/                     # Root directory
├── bin/                     # Compiled binary outputs
│   └── test/                  # Test binary outputs
├── include/                 # Header files
│   ├── ds/                    # Data structure headers
│   │   ├── basec_array.h        # Array header
│   │   ├── basec_queue.h        # Queue header
│   │   └── basec_string.h       # String header
│   └── io/                    # I/O headers
│       └── basec_file.h         # File operations header
├── src/                     # Source code
│   ├── ds/                    # Data structure implementations
│   │   ├── basec_array.c        # Array implementation
│   │   ├── basec_queue.c        # Queue implementation
│   │   └── basec_string.c       # String implementation
│   └── io/                    # I/O implementations
│       └── basec_file.c         # File operations implementation
├── test/                    # Test files
│   ├── ds/                    # Data structure tests
│   │   └── test_string.c        # String tests
│   └── io/                    # I/O tests
│       └── test_file.c          # File tests
└── Makefile                 # Build system
```

## String

- `string_create`   - Create a new String
- `string_resize`   - Resize the capacity of a String
- `string_set`      - Set the value of a String
- `string_length`   - Get the length of a String
- `string_capacity` - Get the capacity of a String
- `string_copy`     - Copy a String
- `string_append`   - Append a String to another String
- `string_concat`   - Concatenate two Strings
- `string_contains` - Check if a String contains another String
- `string_index_of` - Get the index of a substring in a String
- `string_destroy`  - Destroy a String

## Array

- `array_create`    - Create a new Array
- `array_resize`    - Resize the capacity of an Array
- `array_destroy`   - Destroy an Array
- `array_size`      - Get the size of an Array
- `array_capacity`  - Get the capacity of an Array
- `array_add`       - Add an element to an Array
- `array_remove`    - Remove an element from an Array
- `array_get`       - Get an element from an Array
- `array_set`       - Set an element in an Array
- `array_contains`  - Check if an Array contains an element
- `array_index_of`  - Get the index of an element in an Array

## Queue

- `queue_create`    - Create a new Queue
- `queue_resize`    - Resize the capacity of a Queue
- `queue_size`      - Get the size of a Queue
- `queue_capacity`  - Get the capacity of a Queue
- `queue_enqueue`   - Enqueue an element to a Queue
- `queue_dequeue`   - Dequeue an element from a Queue
- `queue_destroy`   - Destroy a Queue

## File Operations

- `file_exists`   - Check if a file exists
- `file_create`   - Create a new file
- `file_open`     - Open an existing file
- `file_remove`   - Remove a file
- `file_destroy`  - Destroy a file handle

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/basec.git
   cd basec
   ```
2. Build the project:
   ```bash
   make build
   ```
3. (Optional) Run tests to verify:
   ```bash
   make test
   ```

## Usage

### Generating Documentation
Generate Doxygen documentation for the project:
```bash
doxygen
```

### Building the Project
Compile the library and tests:
```bash
make build
```

### Running Tests
Execute the test suite:
```bash
make test
```

### Running Examples
Run example programs (if available):
```bash
make run
```