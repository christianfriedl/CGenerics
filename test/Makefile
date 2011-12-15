include Makefile.local
CFLAGS=-Wall -I../
LDFLAGS=-Wall

BINARIES=0500_Array

clean-all: clean all

all: clean $(BINARIES)

clean:
	rm -f *.o $(BINARIES) 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

%: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

pp:
	for i in $(BINARIES); do gcc $(CFLAGS) -E -o - -c $$i.c; done
