# basec is a simple C Base Layer

## Project Structure
```
basec/
├── bin/               # Compiled binary outputs
│   └── test/          # Test binary outputs
├── include/           # Header files
│   └── ds/            # Data structures headers
│       └── string/    # String headers
├── src/               # Source code
│   └── ds/            # Data structures implementation
│       └── string/    # String implementation
├── test/              # Test files
└── Makefile           # Build system
```

## String

- `string_create`   - Create a new String
- `string_set`      - Set the value of a String
- `string_length`   - Get the length of a String
- `string_copy`     - Copy a String
- `string_concat`   - Concatenate two Strings
- `string_contains` - Check if a String contains another String
- `string_index_of` - Get the index of a substring in a String
- `string_destroy`  - Destroy a String

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

- [x] String
  - [x] Create
  - [x] Destroy
  - [x] Set
  - [x] Length
  - [x] Copy
  - [x] Concatenate
  - [x] Contains
  - [x] IndexOf
- [x] Array
  - [x] Create
  - [x] Destroy
  - [x] Size
  - [x] Capacity
  - [x] Add
  - [ ] Remove
  - [ ] Get
  - [ ] Set
  - [ ] Contains
- [ ] DynamicArray
- [ ] Queue
- [ ] Stack