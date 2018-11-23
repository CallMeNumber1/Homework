CC = gcc
CFLAGS = -std=c11 -DTEST_FUNC -Wall -g -lm 
.PHONY: clean

a.out : main.o is_prime.o add.o newtown.o binary.o
	$(CC) $(CFLAGS)  main.o is_prime.o add.o newtown.o binary.o thirdpart/libs/libtest.a

main.o : main.c
	$(CC) -c $(CFLAGS) main.c

is_prime.o : is_prime.c is_prime.h
	$(CC) -c $(CFLAGS) is_prime.c

add.o : add.c add.h
	$(CC) -c $(CFLAGS) add.c

newtown.o : newtown.c newtown.h
	$(CC) -c $(CFLAGS) newtown.c

binary.o : binary.c binary.h
	$(CC) -c $(CFLAGS) binary.c

test.o : test.c test.h
	$(CC) -c $(CFLAGS) test.c
clean : 
	rm -rf *.o a.out
