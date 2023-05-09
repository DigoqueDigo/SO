# COMPILER

CC := gcc
CFLAGS := -Wall -Wextra -pedantic-errors -O2 -Iinclude

# DIRECTORIES

OBJ_DIR := build
OBJS_PACKAGE_DIR := build/package
OBJS_HANDLE_DIR := build/handle
PIDS_FOLDER := pids

# OBJECT CODE

OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(wildcard src/*.c))
OBJS_PACKAGE := $(patsubst src/package/%.c, $(OBJS_PACKAGE_DIR)/%.o, $(wildcard src/package/*.c))
OBJS_HANDLE := $(patsubst src/handle/%.c, $(OBJS_HANDLE_DIR)/%.o, $(wildcard src/handle/*.c))
ALL_OBJS := $(OBJS) $(OBJS_PACKAGE) $(OBJS_HANDLE)

# TERMINAL MESSAGES

DELETING_COLOR := \033[0;31m
DELETING_STRING := "[DELETING...]"

COMPILING_COLOR := \033[0;33m
COMPILING_STRING := "[COMPILING]"

OK_COLOR := \033[0;32m
OK_STRING := "[OK]"

# TARGET

TARGET_MONITOR := monitor
TARGET_TRACER := tracer
TARGET_ZIP := grupo-xx.zip

# BUILDING

all: $(TARGET_MONITOR) $(TARGET_TRACER)
	@printf "$(OK_COLOR)$(OK_STRING)\n"
	@mkdir -p $(PIDS_FOLDER)

# LINKING

$(TARGET_MONITOR): $(filter-out $(OBJ_DIR)/tracer.o, $(ALL_OBJS))
	@$(CC) -o $@ $^


$(TARGET_TRACER): $(filter-out $(OBJ_DIR)/monitor.o, $(ALL_OBJS))
	@$(CC) -o $@ $^

# COMPILING

$(OBJS): $(OBJ_DIR)/%.o : src/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(COMPILING_COLOR)$(COMPILING_STRING) $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@


$(OBJS_PACKAGE): $(OBJS_PACKAGE_DIR)/%.o : src/package/%.c
	@mkdir -p $(OBJS_PACKAGE_DIR)
	@printf "$(COMPILING_COLOR)$(COMPILING_STRING) $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@


$(OBJS_HANDLE): $(OBJS_HANDLE_DIR)/%.o : src/handle/%.c
	@mkdir -p $(OBJS_HANDLE_DIR)
	@printf "$(COMPILING_COLOR)$(COMPILING_STRING) $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

# ZIP

zip:
	@mkdir -p 19
	@cp -r Makefile src/ include/ report/ *.pdf 19/
	zip -rv 19.zip 19/
	unzip -tv 19.zip
	@rm -r 19/

# CLEAN

clean:
	@printf "$(DELETING_COLOR)$(DELETING_STRING)\n"
	@rm -rf $(OBJ_DIR) $(PIDS_FOLDER) $(TARGET_MONITOR) $(TARGET_TRACER)
	@printf "$(OK_COLOR)$(OK_STRING)\n"
