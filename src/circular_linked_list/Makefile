CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g -I../../includes -I./includes

LIB_NAME = libcircularlinkedlist.a

SRC_DIR = src
INC_DIR = includes
TESTS_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))
TEST_SRC = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJ = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/%.o, $(TEST_SRC))

TEST_EXE = test_circular_linked_list

UTILS_OBJ = ../../src/data_structure_utils.o

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES) $(UTILS_OBJ)
	ar rcs $(LIB_NAME) $(OBJ_FILES) $(UTILS_OBJ)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(UTILS_OBJ) -L. -lcircularlinkedlist -o $(TEST_EXE)
	./$(TEST_EXE)

clean:
	rm -f $(LIB_NAME) $(OBJ_FILES) $(TEST_OBJ) $(TEST_EXE)

.PHONY: all test clean