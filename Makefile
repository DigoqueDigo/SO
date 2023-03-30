# COMPILER

CC := gcc
CFLAGS := -Wall -Wextra -pedantic-errors -O2 -Iinclude

# OBJECT CODE

OBJS := $(patsubst %.c, %.o, $(wildcard src/*.c))

# TARGET

TARGET_MONITOR := monitor
TARGET_TRACER := tracer

# BUILDING

all: $(TARGET_MONITOR) $(TARGET_TRACER)

# LINKING

$(TARGET_MONITOR): $(filter-out src/tracer.o, $(OBJS))
	$(CC) -o $@ $^


$(TARGET_TRACER): $(filter-out src/monitor.o, $(OBJS))
	$(CC) -o $@ $^

# COMPILING

$(OBJS): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# CLEAN

clean:
	rm $(OBJS)
	rm $(TARGET_MONITOR)
	rm $(TARGET_TRACER)
