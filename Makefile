CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c2x

SRC_DIR=src
INC_DIR=include
BIN_DIR=bin

TEST_DIR=test
TEST_BIN_DIR=test/bin

SRC=$(wildcard $(SRC_DIR)/*.c)
SRC_INCLUDE=$(wildcard $(INC_DIR)/*.h)

TEST_SRC=$(wildcard $(TEST_DIR)/*.c)
TEST_BINS=$(patsubst $(TEST_DIR)/%.c,$(TEST_BIN_DIR)/%,$(TEST_SRC))

build: basec

basec: $(SRC) $(SRC_INCLUDE)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(BIN_DIR)/basec $(SRC)

run: basec
	$(BIN_DIR)/basec

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(SRC) $(SRC_INCLUDE)
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $< $(SRC_DIR)/basec_*.c

test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		$$test; \
	done

clean:
	rm -rf $(BIN_DIR) $(TEST_BIN_DIR)