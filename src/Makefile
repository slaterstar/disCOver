CC = gcc # Flag for implicit rules
CFLAGS = -g -Wall # Flag for implicit rules. Turn on debug info

LIF_DIR:=./src/lifter
DIS_DIR:=./src/disassembler
DAT_DIR:=./src/datastructures

default: lifter discover

lifter:
	-@MKDIR -p "./bin" 2>NUL || true
	$(CC) $(CFLAGS) $(LIF_DIR)/main.c $(LIF_DIR)/lift.c $(DAT_DIR)/dynamicarray.c $(LIF_DIR)/ir.c $(DIS_DIR)/disassemble.c -o ./bin/lifter

discover:
	-@MKDIR -p "./bin" 2>NUL || true
	$(CC) $(CFLAGS) $(DIS_DIR)/main.c $(DIS_DIR)/disassemble.c $(DAT_DIR)/dynamicarray.c -o ./bin/discover

clean:
	rm -rf "./bin"
