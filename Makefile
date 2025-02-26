# Compiler
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c2x

# Directories
SRC_DIR=src
INC_DIR=include
TEST_DIR=test

# Output directories
BIN_DIR=bin
TEST_BIN_DIR=bin/test

# Source files
SRC=$(shell find $(SRC_DIR) -name "*.c")
SRC_NO_MAIN=$(shell find $(SRC_DIR) -name "*.c" ! -name "main.c")
INCLUDE=$(shell find $(INC_DIR) -name "*.h")

# Test files
TEST_SRC=$(shell find $(TEST_DIR) -name "*.c")
TEST_INCLUDE=$(shell find $(INC_DIR) -name "*.h")

# Phony targets
.PHONY: build run test clean

# Build target
build: $(SRC) $(INCLUDE)
	@# Create the bin directory if it doesn't exist
	@mkdir -p $(BIN_DIR)

	@# Compile the basec executable
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o $(BIN_DIR)/basec $(SRC)

# Run target
run: build
	@# Run the basec executable
	@$(BIN_DIR)/basec

# Test target
test:
	@# Create the test bin directory if it doesn't exist
	@mkdir -p $(TEST_BIN_DIR)

	@# Compile and run each test file
	@for test_file in $(TEST_SRC); do \
		base_name=$$(basename $$test_file .c); \
		$(CC) $(CFLAGS) -I$(INC_DIR) -o $(TEST_BIN_DIR)/$$base_name $$test_file $(SRC_NO_MAIN); \
		./$(TEST_BIN_DIR)/$$base_name; \
	done

# Clean target
clean:
	@# Remove the bin directories
	@rm -rf $(BIN_DIR)
	@rm -rf $(TEST_BIN_DIR)