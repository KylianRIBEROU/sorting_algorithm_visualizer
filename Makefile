# --- Makefile for Sorting Visualization Project ---

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c17
LDFLAGS = -lSDL2

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN = sortviz

# Source and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: $(OBJ_DIR) $(BIN)

# Build binary
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compile each .c into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean objects and binary
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(BIN)

re: fclean all

run: all
	./$(BIN)
