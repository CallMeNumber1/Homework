CC = gcc
CFLAGS = -std=c11 -Wall -g
.PHONY: clean

a.out : main.o get_conf_value.o socket_create.o common.o delete_node.o insert.o isrepeat.o find_min.o
	$(CC) $(CFLAGS) main.o get_conf_value.o socket_create.o common.o delete_node.o insert.o isrepeat.o find_min.o -lpthread

main.o : main.c
	$(CC) -c $(CFLAGS) main.c -lpthread

get_conf_value.o : get_conf_value.c get_conf_value.h
	$(CC) -c $(CFLAGS) get_conf_value.c

socket_create.o : socket_create.c socket_create.h
	$(CC) -c $(CFLAGS) socket_create.c

common.o : common.c common.h
	$(CC) -c $(CFLAGS) common.c

delete_node.o : delete_node.c delete_node.h
	$(CC) -c ${CFLAGS} delete_node.c

insert.o : insert.c insert.h
	$(CC) -c ${CFLAGS} insert.c

isrepeat.o : isrepeat.c isrepeat.h
	$(CC) -c $(CFLAGS) isrepeat.c

find_min.o : find_min.c find_min.h
	$(CC) -c $(CFLAGS) find_min.c


clean :
	rm -rf *.o a.out
