CC = gcc
CFLAGS = -g -Wall -Iinclude

# Output Directories
BIN_DIR = bin
BUILD_DIR = build


LIFTER_SRCS = tools/lifter_main.c \
              src/lifter/lift.c \
              src/lifter/ir.c \
              src/datastructures/dynamicarray.c \
              src/disassembler/disassemble.c

DISCOVER_SRCS = tools/discover_main.c \
                src/disassembler/disassemble.c \
                src/datastructures/dynamicarray.c


LIFTER_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(LIFTER_SRCS))
DISCOVER_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(DISCOVER_SRCS))


default: lifter discover

lifter: $(LIFTER_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

discover: $(DISCOVER_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@


$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR) compile_commands.json