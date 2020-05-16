CFLAGS=-std=c11 -g -static
OBJECTS:=$(patsubst %.c,%.o,$(wildcard *.c))

ivcc: $(OBJECTS)
		$(CC) -o ivcc $(CFLAGS) $(LDFLAGS) $(OBJECTS)

$(OBJECTS): ivcc.h

test: ivcc
		./test.sh

clean:
		rm -rf ivcc *.o *~ tmp* ivcc.dSYM*

.PHONY: test clean

