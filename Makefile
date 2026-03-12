ifeq ($(OS),Windows_NT)
    RM = powershell -Command "Remove-Item -Recurse -Force -ErrorAction Ignore"
    MKDIR = powershell -Command "New-Item -ItemType Directory -Force"
    EXE = .exe
    FIXPATH = $(subst /,\,$1)
else
    RM = rm -rf
    MKDIR = mkdir -p
    EXE =
    FIXPATH = $1
endif

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3 -DNDEBUG

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests
EXAMPLE_DIR = examples
TEST_BIN_DIR = bin/tests
EXAMPLE_BIN_DIR = bin/examples

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%$(EXE), $(TEST_SRCS))

EXAMPLE_SRCS = $(wildcard $(EXAMPLE_DIR)/*.c)
EXAMPLE_BINS = $(patsubst $(EXAMPLE_DIR)/%.c, $(EXAMPLE_BIN_DIR)/%$(EXE), $(EXAMPLE_SRCS))

TARGET = libds.a

.PHONY: all clean debug release test examples

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

$(TEST_BIN_DIR):
	$(MKDIR) $(TEST_BIN_DIR)

$(EXAMPLE_BIN_DIR):
	$(MKDIR) $(EXAMPLE_BIN_DIR)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

release: CFLAGS += $(RELEASE_FLAGS)
release: clean all

test: debug $(TEST_BINS)
ifeq ($(OS),Windows_NT)
	@for %%f in ($(call FIXPATH,$(TEST_BINS))) do ( echo Running %%f... & %%f )
else
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done
endif

$(TEST_BIN_DIR)/%$(EXE): $(TEST_DIR)/%.c $(TARGET) | $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $< -L. -lds -o $@

examples: $(TARGET) $(EXAMPLE_BINS)
ifeq ($(OS),Windows_NT)
	@for %%f in ($(call FIXPATH,$(EXAMPLE_BINS))) do ( echo Running %%f... & %%f )
else
	@for example in $(EXAMPLE_BINS); do \
		echo "Running $$example..."; \
		./$$example; \
	done
endif

$(EXAMPLE_BIN_DIR)/%$(EXE): $(EXAMPLE_DIR)/%.c $(TARGET) | $(EXAMPLE_BIN_DIR)
	$(CC) $(CFLAGS) $< -L. -lds -o $@

clean:
	$(RM) $(OBJ_DIR) bin $(TARGET)
