CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g -I../../includes -I./includes

LIB_NAME = libvector.a

SRC_DIR = src
INC_DIR = includes
TESTS_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))
TEST_SRC = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJ = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/%.o, $(TEST_SRC))

TEST_EXE = test_vector

# Vector does not strictly depend on data_structure_utils.o for resizing logic anymore
# as we implemented it directly with realloc, but we might need it if we change implementation.
# For now, we don't link it unless needed, but to be consistent with other modules:
UTILS_OBJ = ../../src/data_structure_utils.o

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES)
	ar rcs $(LIB_NAME) $(OBJ_FILES)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_OBJ) -L. -lvector -o $(TEST_EXE)
	./$(TEST_EXE)

clean:
	rm -f $(LIB_NAME) $(OBJ_FILES) $(TEST_OBJ) $(TEST_EXE)

.PHONY: all test clean
