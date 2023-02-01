MKDIR  = mkdir -p
REMOVE = rm -rf

CC     = clang
CFLAGS = -g -Wall -std=c17

MKFILE_PATH = $(abspath $(lastword $(MAKEFILE_LIST)))
MKFILE_DIR  = $(dir $(MKFILE_PATH))

PROJECT_NAME      = cboxes

PROJECT_DIR = $(MKFILE_DIR:-=)

INCLUDE_DIR = $(PROJECT_DIR)include
SOURCES_DIR = $(PROJECT_DIR)src
BUILD_DIR   = $(PROJECT_DIR)build
TESTS_DIR   = $(PROJECT_DIR)tests

LIBRARY     = $(BUILD_DIR)/lib$(PROJECT_NAME).a

OBJ_DIR       = $(BUILD_DIR)/objs
TESTS_BIN_DIR = $(BUILD_DIR)/tests

TESTS_SOURCES = $(wildcard $(TESTS_DIR)/*.c)
TESTS_BINS    = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_BIN_DIR)/%, $(TESTS_SOURCES))

SOURCES = $(wildcard $(SOURCES_DIR)/*.c)
HEADERS = $(wildcard $(INCLUDE_DIR)/**/*.h)
OBJS    = $(patsubst $(SOURCES_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))


FORMATTER = clang-format
FORMATTER_FLAGS = -i


default: all
all: $(LIBRARY)

release: CFLAGS=-Wall -O3 -DNDEBUG
release: clean
release: $(LIBRARY)


$(LIBRARY): $(BUILD_DIR) $(OBJ_DIR) $(OBJS)
	$(RM) $(LIBRARY)
	ar -cvrs $(LIBRARY) $(OBJS)

$(BUILD_DIR):
	$(MKDIR) $@

$(OBJ_DIR):
	$(MKDIR) $@

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.c $(INCLUDE_DIR)/$(PROJECT_NAME)/%.h
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(TESTS_BIN_DIR)/%: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion -I$(INCLUDE_DIR)

tests: $(LIBRARY) $(TESTS_BIN_DIR) $(TESTS_BINS)
	@for test in $(TESTS_BINS); do $$test ; done

$(TESTS_BIN_DIR):
	$(MKDIR) $@


clean veryclean:
	$(REMOVE) $(BUILD_DIR)

format-source:
	$(FORMATTER) $(FORMATTER_FLAGS) $(SOURCES)
	$(FORMATTER) $(FORMATTER_FLAGS) $(HEADERS)

format-tests:
	$(FORMATTER) $(FORMATTER_FLAGS) $(TESTS_SOURCES)

format: format-source format-tests

.PHONY: default, all, main, clean

