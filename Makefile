# Directories
OBJ_DIR = build
IDIR = include
SRC_DIR = src
TEST_DIR = tests

# Compiler
CC = g++
CFLAGS = -I$(IDIR) -std=c++20

# Source files
LIB_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(LIB_SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

# Executables
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%,$(TEST_SRCS))

# Rule to build all test executables
all_tests: $(TEST_EXECUTABLES)

# Rule to build each test executable
$(OBJ_DIR)/%: $(OBJ_DIR)/%.o $(LIB_OBJS)
	@echo "generating: $@"
	$(CC) -o $@ $^ $(CFLAGS)

# Rule to compile library source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(IDIR)/*.h) | $(OBJ_DIR)
	@echo "generating: $@"
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to compile test source files into object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(wildcard $(IDIR)/*.h) | $(OBJ_DIR)
	@echo "generating: $@"
	$(CC) -c -o $@ $< $(CFLAGS)

# Ensure object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

# Run rule to execute all test executables
.PHONY: run_tests
run: all_tests
	@for test in $(TEST_EXECUTABLES); do ./$$test; done