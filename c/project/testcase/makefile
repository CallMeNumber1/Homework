CC = gcc
CFLAGS =  -std=c11 -Wall -g
INCLUDES = -I./include

.PHONY: clean

libtest.a : test.o
	ar crv libtest.a test.o

test.o : src/test.c include/test.h
	$(CC) -c $(CFLAGS) $(INCLUDES)  src/test.c

install:
	cp libtest.a output/libs
	cp include/* output/include

clean : 
	rm -rf *.o *.a
