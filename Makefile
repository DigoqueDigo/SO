# COMPILER

CC := gcc
CFLAGS := -Wall -Wextra -pedantic-errors -O2 -Iinclude

# DIRECTORIES

OBJ_DIR := build

# OBJECT CODE

OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(wildcard src/*.c))

# TERMINAL MESSAGES

DELETING_COLOR = \033[0;31m
DELETING_STRING = "[DELETING...]"

COMPILING_COLOR = \033[0;33m
COMPILING_STRING = "[COMPILING]"

OK_COLOR = \033[0;32m
OK_STRING = "[OK]"

# TARGET

TARGET_MONITOR := monitor
TARGET_TRACER := tracer

# BUILDING

all: $(TARGET_MONITOR) $(TARGET_TRACER)
	@printf "$(OK_COLOR)$(OK_STRING)\n"

# LINKING

$(TARGET_MONITOR): $(filter-out $(OBJ_DIR)/tracer.o, $(OBJS))
	@$(CC) -o $@ $^


$(TARGET_TRACER): $(filter-out $(OBJ_DIR)/monitor.o, $(OBJS))
	@$(CC) -o $@ $^

# COMPILING

$(OBJS): $(OBJ_DIR)/%.o : src/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(COMPILING_COLOR)$(COMPILING_STRING) $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

# CLEAN

clean:
	@printf "$(DELETING_COLOR)$(DELETING_STRING)\n"
	@rm -rf $(OBJ_DIR) $(TARGET_MONITOR) $(TARGET_TRACER)
	@printf "$(OK_COLOR)$(OK_STRING)\n"
