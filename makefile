CC = gcc
CFLAGS = -Wall -ansi -pedantic

all: ds_memory.o ds_array.o ds_list.o

ds_memory.o: ds_memory.c
	$(CC) $(CFLAGS) ds_memory.c -c -o ds_memory.o

ds_array.o: ds_array.c
	$(CC) $(CFLAGS) ds_array.c -c -o ds_array.o

ds_list.o: ds_list.c
	$(CC) $(CFLAGS) ds_list.c -c -o ds_list.o
