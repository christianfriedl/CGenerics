include Makefile.local
CFLAGS=-Wall -I../
LDFLAGS=-Wall -L../ -lcgenerics

BINARIES=0500_Array 0501_ArrayPerformance # 0750_LinkedList

clean-all: clean all

all: clean $(BINARIES)

clean:
	rm -f *.o *.e *.e.c *.BAK $(BINARIES) 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

%: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

pp:
	for i in $(BINARIES); do gcc $(CFLAGS) -E -o - -c $$i.c; done

pp-indent:
	for i in $(BINARIES); do gcc $(CFLAGS) -E -o $$i.e.c -c $$i.c && indent -bad -bap -i4 $$i.e.c && gcc -o $$i.e $$i.e.c; done
