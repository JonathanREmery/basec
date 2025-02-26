# basec
basec is a C Base Layer, with a focus on memory safety and efficiency.

## Project Structure
```
basec/                     # Root directory
├── bin/                    # Compiled binary outputs
│   └── test/                # Test binary outputs
├── include/                # Header files
│   └── ds/                  # Data structures headers
│       └── basec_string.h    # String header
│       └── basec_array.h     # Array header
├── src/                    # Source code
│   └── ds/                  # Data structures implementation
│       └── basec_string.c    # String implementation
│       └── basec_array.c     # Array implementation
├── test/                   # Test files
└── Makefile                # Build system
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

## Generating Documentation

```bash
doxygen
```

## Building

```bash
make build
```

## Testing

```bash
make test
```

## Running

```bash
make run
```

## Roadmap

- [x] Queue
  - [x] queue_create
  - [x] queue_resize
  - [x] queue_size
  - [x] queue_capacity
  - [x] queue_enqueue
  - [x] queue_dequeue
  - [x] queue_destroy
- [ ] Stack
- [ ] Deque
- [ ] Linked List