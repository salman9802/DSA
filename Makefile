# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -Ithird_party/munit
AR = ar rcs

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build

# Output files
LIB = $(BUILD_DIR)/libdsa.a
TEST_BIN = $(BUILD_DIR)/test_runner.exe

# File discovery
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_FILES = $(filter-out $(TEST_DIR)/test_runner.c, $(wildcard $(TEST_DIR)/*.c))
THIRD_PARTY_FILES = $(wildcard third_party/munit/*.c)

# Default target
all: $(LIB)

# Ensure build directory exists
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build static library
$(LIB): $(OBJ_FILES)
	$(AR) $@ $^

# --- TESTING SECTION ---
test: $(LIB)
	@echo "Building tests..."
	$(CC) $(CFLAGS) $(TEST_DIR)/test_runner.c $(TEST_FILES) $(THIRD_PARTY_FILES) $(LIB) -o $(TEST_BIN)
	@echo "Running tests..."
	@$(TEST_BIN)

# Clean up
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@echo "Cleaned."

.PHONY: all clean test
