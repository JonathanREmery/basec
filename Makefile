CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c2x

SRC_DIR=src
INC_DIR=include
BIN_DIR=bin

SRC=$(wildcard $(SRC_DIR)/*.c)
SRC_INCLUDE=$(wildcard $(INC_DIR)/*.h)

build: basec

basec: $(SRC) $(SRC_INCLUDE)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(BIN_DIR)/basec $(SRC)

run: basec
	$(BIN_DIR)/basec

clean:
	rm -rf $(BIN_DIR)