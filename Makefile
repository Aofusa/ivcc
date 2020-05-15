CFLAGS=-std=c11 -g -static

ivcc: ivcc.c

test: ivcc
		./test.sh

clean:
		rm -rf ivcc *.o *~ tmp* ivcc.dSYM*

.PHONY: test clean

