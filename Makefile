.PHONY: default all main clean veryclean format format-source format-tests

MKDIR  = mkdir -p
REMOVE = rm -rf

CC     = clang
CFLAGS = -std=c2x

CFLAGS_SECURE = -Wall
CFLAGS_SECURE += -Werror
CFLAGS_SECURE += -Wextra
CFLAGS_SECURE += -Wpedantic
CFLAGS_SECURE += -Wuninitialized
CFLAGS_SECURE += -Wmissing-include-dirs
CFLAGS_SECURE += -Wshadow
CFLAGS_SECURE += -Wundef
CFLAGS_SECURE += -Warc-repeated-use-of-weak
CFLAGS_SECURE += -Wbitfield-enum-conversion
CFLAGS_SECURE += -Wconditional-uninitialized
CFLAGS_SECURE += -Wthread-safety
CFLAGS_SECURE += -Wconversion
CFLAGS_SECURE += -Wswitch -Wswitch-enum
CFLAGS_SECURE += -Wformat-security
CFLAGS_SECURE += -Wdouble-promotion
CFLAGS_SECURE += -Wfloat-equal
CFLAGS_SECURE += -Wfloat-overflow-conversion
CFLAGS_SECURE += -Wfloat-zero-conversion
CFLAGS_SECURE += -Wsign-compare
CFLAGS_SECURE += -Wsign-conversion

AR      = ar
ARFLAGS = -cvrs

PROJECT_NAME = cboxes

PROJECT_DIR = $(CURDIR)

INCLUDE_DIR = $(PROJECT_DIR)/include
SOURCES_DIR = $(PROJECT_DIR)/src
BUILD_DIR   = $(PROJECT_DIR)/build
TESTS_DIR   = $(PROJECT_DIR)/tests

LIBRARY     = $(BUILD_DIR)/lib$(PROJECT_NAME).a

OBJ_DIR       = $(BUILD_DIR)/objs
TESTS_BIN_DIR = $(BUILD_DIR)/tests

TESTS_SOURCES = $(wildcard $(TESTS_DIR)/*.c)
TESTS_BINS    = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_BIN_DIR)/%, $(TESTS_SOURCES))

SOURCES = $(wildcard $(SOURCES_DIR)/*.c)
HEADERS = $(wildcard $(INCLUDE_DIR)/**/*.h)
OBJS    = $(patsubst $(SOURCES_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

INCLUDE_FLAGS = -I$(INCLUDE_DIR)

FORMATTER = clang-format
FORMATTER_FLAGS = -i

PY_COMP_DB      = compiledb
PY_ENV          = $(PROJECT_DIR)/.env
PY_ENV_BIN      = $(PY_ENV)/bin
PY_PIP_EXEC     = $(PY_ENV_BIN)/pip
PY_COMP_DB_EXEC = $(PY_ENV_BIN)/compiledb

COMPILE_COMMANDS = $(PROJECT_DIR)/compile_commands.json

CLANG_TIDY = clang-tidy
CLANG_TIDY_FLAGS = -p $(COMPILE_COMMANDS)

TARGETS = $(LIBRARY)

all: debug

debug: CFLAGS += -g -O0 -D__DEBUG_MODE__
debug: $(TARGETS)

release: CFLAGS += -O3 -D__RELEASE__MODE__
release: clean
release: $(TARGETS)

asan: CFLAGS += -fsanitize=address -fno-optimize-sibling-calls -fno-omit-frame-pointer
asan: debug

lsan: CFLAGS += -fsanitize=leak
lsan: debug

msan: CFLAGS += -fsanitize=memory -fno-optimize-sibling-calls -fno-omit-frame-pointer
msan: debug

ubsan: CFLAGS += -fsanitize=undefined
ubsan: debug

configure: $(COMPILE_COMMANDS)

clean:
	$(REMOVE) $(BUILD_DIR)

veryclean: clean
	$(REMOVE) $(PY_ENV)
	$(REMOVE) $(COMPILE_COMMANDS)

$(LIBRARY): $(BUILD_DIR) $(OBJ_DIR) $(OBJS)
	$(RM) $(LIBRARY)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJS)

$(BUILD_DIR):
	$(MKDIR) $@

$(OBJ_DIR):
	$(MKDIR) $@

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.c $(INCLUDE_DIR)/$(PROJECT_NAME)/%.h
	[ -f $(COMPILE_COMMANDS) ] && $(CLANG_TIDY) $(CLANG_TIDY_FLAGS) $< || true
	$(CC) $(CFLAGS) $(CFLAGS_SECURE) -c $< -o $@ $(INCLUDE_FLAGS)

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.c
	[ -f $(COMPILE_COMMANDS) ] && $(CLANG_TIDY) $(CLANG_TIDY_FLAGS) $< || true
	$(CC) $(CFLAGS) $(CFLAGS_SECURE) -c $< -o $@ $(INCLUDE_FLAGS)

tests: $(LIBRARY) $(TESTS_BIN_DIR) $(TESTS_BINS)
	@for test in $(TESTS_BINS); do $$test --verbose=1 ; done

$(TESTS_BIN_DIR)/%: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion $(INCLUDE_FLAGS)

$(TESTS_BIN_DIR):
	$(MKDIR) $@

$(COMPILE_COMMANDS): $(PY_COMP_DB_EXEC)
	$< make all tests -o $@

$(PY_COMP_DB_EXEC):
	python -m venv $(PY_ENV)
	$(PY_PIP_EXEC) install $(PY_COMP_DB)

checks:
	sh ./scripts/run_checks.sh

install:
	@echo todo

# Formatting
format-source:
	$(FORMATTER) $(FORMATTER_FLAGS) $(SOURCES)
	$(FORMATTER) $(FORMATTER_FLAGS) $(HEADERS)

format-tests:
	$(FORMATTER) $(FORMATTER_FLAGS) $(TESTS_SOURCES)

format: format-source format-tests

# Testing executable
TESTING_DIR = $(PROJECT_DIR)/testing
TESTING_SRC = $(TESTING_DIR)/testing.c
TESTING_OUT = $(BUILD_DIR)/testing

$(TESTING_OUT): $(LIBRARY)
	$(RM) $(TESTING_OUT)
	$(CC) $(CFLAGS) $(TESTING_SRC) $< -o $@ -I$(INCLUDE_DIR)

testing: $(TESTING_OUT)

run: testing
	$(TESTING_OUT)

