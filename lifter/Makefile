CC = gcc # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info

SRC_DIR:=src

default:
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o ./bin/lifter

clean:
	rm -f ./bin/*
