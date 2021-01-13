.PHONY: all clean

read: read.c lookup.h
	$(CC) read.c -o read -O0

all: read
	
clean:
	rm read

