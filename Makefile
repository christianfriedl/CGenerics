CFLAGS=-ggdb
LDFLAGS=-ggdb

BINARIES=usearray

usearray: usearray.o Array.h

pp:
	cc -c -E usearray.c

clean:
	rm *.o *.a $(BINARIES)
