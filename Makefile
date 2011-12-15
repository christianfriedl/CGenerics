CFLAGS=-ggdb
LDFLAGS=-ggdb

usearray: usearray.o Array.h

pp:
	cc -c -E usearray.c
