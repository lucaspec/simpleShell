CC = gcc
CFLAGS = -Wall -I./include

SRC_DIR = src
OBJ_DIR = obj

# List of source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
# Generate object file names from source file names
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
# Name of the main program
MAIN = shell

# Default target
all: $(MAIN)

# Rule to create the main program
$(MAIN): $(OBJ_FILES)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove compiled files
clean:
	rm -rf $(OBJ_DIR)