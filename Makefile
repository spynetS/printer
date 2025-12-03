# Compiler and flags
CC=gcc
CFLAGS=-Wall -fPIC -I./include # Add -fPIC for shared libs. -I for headers.
LDFLAGS=-shared
BUILD_DIR=build
SRC_DIR=src

# List of object files
OBJS = $(BUILD_DIR)/Canvas.o $(BUILD_DIR)/msc.o

# Targets
TARGET_A = $(BUILD_DIR)/libprinter.a
TARGET_SO = $(BUILD_DIR)/libprinter.so

# Default target
all: $(TARGET_A) $(TARGET_SO)

# Rule to build the shared library from object files
$(TARGET_SO): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to build the static library
$(TARGET_A): $(OBJS)
	ar rcs $@ $^

# Pattern rule to compile any .c file into a .o file in the build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR) # Create build directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

example1: ./examples/example1.c $(OBJS)
	$(CC) $(CFLAGS) -lm -o example1 ./examples/example1.c $(OBJS)
# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
