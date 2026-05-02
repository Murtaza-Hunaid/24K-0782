CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = banker_simulator

# All source files
SRCS = main.c \
       data_structures.c \
       safety_algorithm.c \
       request_handler.c \
       rollback.c \
       performance.c \
       resource_manager.c \
       visualization.c \
       interactive_input.c \
       logger.c

OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
%.o: %.c banker.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET) *.txt

# Rebuild from scratch
rebuild: clean all

# Run the simulator
run: $(TARGET)
	./$(TARGET)

# Debug build with extra flags
debug: CFLAGS += -DDEBUG -O0
debug: clean all

# Release build with optimizations
release: CFLAGS += -O2
release: clean all

.PHONY: all clean rebuild run debug release
