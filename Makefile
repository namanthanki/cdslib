CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g -I$(INC_DIR) -I./includes

# Directories
SRC_DIR = src
INC_DIR = includes
TESTS_DIR = tests

# Data structure directories
ARRAY_DIR = $(SRC_DIR)/array
QUEUE_DIR = $(SRC_DIR)/queue
STACK_DIR = $(SRC_DIR)/stack

# Libraries
ARRAY_LIB = $(ARRAY_DIR)/libarray.a
QUEUE_LIB = $(QUEUE_DIR)/libqueue.a
STACK_LIB = $(STACK_DIR)/libstack.a

# Utility files
UTILS_SRC = $(SRC_DIR)/data_structure_utils.c
UTILS_OBJ = $(SRC_DIR)/data_structure_utils.o

# Main targets
all: utils array queue stack

utils: $(UTILS_OBJ)

array: utils
    $(MAKE) -C $(ARRAY_DIR) INC_DIR="$(CURDIR)/$(INC_DIR)"

queue: utils
    $(MAKE) -C $(QUEUE_DIR) INC_DIR="$(CURDIR)/$(INC_DIR)"

stack: utils
    $(MAKE) -C $(STACK_DIR) INC_DIR="$(CURDIR)/$(INC_DIR)"

# Compile utility object file
$(UTILS_OBJ): $(UTILS_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Tests
test: test_array test_queue test_stack

test_array: array
	$(MAKE) -C $(ARRAY_DIR) test

test_queue: queue
	$(MAKE) -C $(QUEUE_DIR) test

test_stack: stack
	$(MAKE) -C $(STACK_DIR) test

# Clean
clean:
	$(MAKE) -C $(ARRAY_DIR) clean
	$(MAKE) -C $(QUEUE_DIR) clean
	$(MAKE) -C $(STACK_DIR) clean
	rm -f $(UTILS_OBJ)

.PHONY: all utils array queue stack test test_array test_queue test_stack clean