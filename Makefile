# Strict C Project Makefile
CC        := clang
CFLAGS    := -std=c17 -Wall -Wextra -Werror -pedantic -pedantic-errors
CFLAGS    += -Wshadow -Wconversion -Wsign-conversion -Wcast-qual
CFLAGS    += -Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition
CFLAGS    += -Wredundant-decls -Wnested-externs -Wformat=2
CFLAGS    += -Wundef -Wwrite-strings -Wcast-align -Wpointer-arith
CFLAGS    += -fno-common -fstack-protector-strong

DEBUG_FLAGS   := -g3 -O0 -fsanitize=address,undefined -fno-omit-frame-pointer
RELEASE_FLAGS := -O2 -DNDEBUG

SRC_DIR   := src
BUILD_DIR := build
INC_DIR   := include

SRCS      := $(shell find $(SRC_DIR) -name '*.c')
OBJS      := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d)

TARGET    := main

.PHONY: all debug release clean format lint check

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

# Format all source files
format:
	find $(SRC_DIR) $(INC_DIR) -name '*.c' -o -name '*.h' | xargs clang-format -i

# Check formatting without modifying
format-check:
	find $(SRC_DIR) $(INC_DIR) -name '*.c' -o -name '*.h' | xargs clang-format --dry-run --Werror

# Run clang-tidy
lint:
	find $(SRC_DIR) -name '*.c' | xargs clang-tidy -p $(BUILD_DIR) -- $(CFLAGS) -I$(INC_DIR)

# Full check: format + lint
check: format-check lint

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)
