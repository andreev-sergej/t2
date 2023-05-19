CC := gcc
CFLAGS := -lm -Wall

NAME := output
TEST_NAME := testi
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./obj

SRC := $(wildcard $(SRC_DIR)/*.c) 

MAIN_SRC := $(SRC)
MAIN_SRC = $(filter-out $(SRC_DIR)/test.c, $(SRC))

TEST_SRC := $(SRC)
TEST_SRC = $(filter-out $(SRC_DIR)/main.c, $(SRC))

OBJ := $(MAIN_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET := $(BIN_DIR)/$(NAME)
TEST_TARGET := $(BIN_DIR)/$(TEST_NAME)

.PHONY: all clean make run valgrind gdb tests

all: CFLAGS += -Ofast
all: $(TARGET)

debug: CFLAGS += -g -O0
debug: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

gdb:
	make clean && make debug && gdb $(TARGET)

run:
	make && $(TARGET)

valgrind:
	make debug && valgrind --leak-check=full --track-origins=yes $(TARGET)

tests:
	$(CC) $(CFLAGS) -g -O0 $(TEST_SRC) -o $(TEST_TARGET) -lm && $(TEST_TARGET)
	rm -f $(TEST_TARGET)

clean:
	rm -f $(OBJ) $(TARGET)