CC = gcc # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info

SRC_DIR:=src

default:
	-@MKDIR -p "./bin" 2>NUL || true
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(SRC_DIR)/disassemble.c -o ./bin/discover

clean:
	rm -rf "./bin"
