CC=cc
CFLAGS=-std=c11 -g -static
OBJECTS:=$(patsubst %.c,%.o,$(wildcard *.c))

ivcc: $(OBJECTS)
		$(CC) -o ivcc $(CFLAGS) $(OBJECTS)

test: ivcc
		./test.sh

clean:
		rm -rf ivcc *.o *~ tmp* ivcc.dSYM*

.PHONY: test clean

