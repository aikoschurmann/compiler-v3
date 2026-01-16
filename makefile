# Makefile (improved)
OUT_DIR := out
SRC_DIR := src
TEST_DIR := tests
OBJ_DIR := obj

CC := gcc

# Base flags (no LTO by default)
CFLAGS_BASE := -Iinclude -Iinclude/cli -Iinclude/core -Iinclude/datastructures -Iinclude/lexing -Iinclude/parsing -Iinclude/sema -Iinclude/types -MMD -MP -g -O3
LDFLAGS_BASE := -lm

# Allow SANITIZE to be passed on the command line: e.g. make SANITIZE=asan
ifdef SANITIZE
  ifeq ($(SANITIZE),asan)
    CFLAGS := $(CFLAGS_BASE) -O1 -fsanitize=address,undefined -fno-omit-frame-pointer -fno-common
    LDFLAGS := $(LDFLAGS_BASE) -fsanitize=address,undefined
  else
    CFLAGS := $(CFLAGS_BASE)
    LDFLAGS := $(LDFLAGS_BASE)
  endif
else
  CFLAGS := $(CFLAGS_BASE)
  LDFLAGS := $(LDFLAGS_BASE)
endif

# Allow a debug target to force -O0 -g
ifdef DEBUG_BUILD
  CFLAGS := -Iinclude -MMD -MP -g -O0
endif

NAME := compiler

# Gather sources (supports nested directories)
SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.c")
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)

# Map source files -> object files under OBJ_DIR preserving subdirs
SRC_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_FILES))
OBJ_FILES := $(SRC_OBJ_FILES) $(TEST_OBJ_FILES)

# Dependency files
DEP_FILES := $(OBJ_FILES:.o=.d)

.PHONY: all clean run asan debug lexer-test

# Default target
all: $(OUT_DIR)/$(NAME)

# Shortcut to build and run ASAN instrumented binary
asan:
	@$(MAKE) clean
	@$(MAKE) SANITIZE=asan all
	@echo "Running with ASAN (abort-on-error)"
	@ASAN_OPTIONS=abort_on_error=1 ./$(OUT_DIR)/$(NAME) ./input/test.rs --time 

# Debug build (no optimization)
debug:
	@$(MAKE) clean
	@$(MAKE) DEBUG_BUILD=1 all
	@echo "Built debug binary: ./$(OUT_DIR)/$(NAME)"



# Build main executable (exclude lexer_test.o if present)
$(OUT_DIR)/$(NAME): $(filter-out $(OBJ_DIR)/lexer_test.o,$(OBJ_FILES))
	@mkdir -p $(OUT_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# Build lexer test executable (exclude main.o)
$(OUT_DIR)/lexer_test: $(filter-out $(OBJ_DIR)/main.o,$(OBJ_FILES))
	@mkdir -p $(OUT_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# Generic rule for compiling sources under SRC_DIR -> OBJ_DIR preserving path
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Generic rule for compiling tests
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files for header tracking (optional)
-include $(DEP_FILES)

clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

# Run the compiled program (default run)
run: all
	./$(OUT_DIR)/$(NAME) ./input/test.txt --types --ast --tokens

bench: all
	./$(OUT_DIR)/$(NAME) ./input/test.txt 


# Run timing-only (example)
time: all
	./$(OUT_DIR)/$(NAME) ./input/test.txt --time

