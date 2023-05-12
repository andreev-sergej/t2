CC := gcc
CFLAGS := -lm -Wall

NAME := output
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./obj

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET := $(BIN_DIR)/$(NAME)

.PHONY: all clean make run valgrind gdb

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
	$(TARGET)

valgrind:
	make debug && valgrind --leak-check=full --track-origins=yes $(TARGET)

clean:
	rm -f $(OBJ)