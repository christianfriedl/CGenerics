include Makefile.local
CFLAGS=-Wall -I../
LDFLAGS=-Wall -L../ -lcgenerics

BINARIES=0250_Integer 0375_CGString 0500_Array 0750_LinkedList
PERFORMANCE_BINARIES=0501_ArrayPerformance 

clean-all: clean all

all: clean tests performance

tests: $(BINARIES)

performance: $(PERFORMANCE_BINARIES)

clean:
	rm -f *.o *.e *.e.c *.BAK $(BINARIES) $(PERFORMANCE_BINARIES)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(CFLAGS)

pp:
	for i in $(BINARIES); do gcc $(CFLAGS) -E -o - -c $$i.c; done

pp-indent:
	for i in $(BINARIES); do gcc $(CFLAGS) -E -o $$i.e.c -c $$i.c && indent -bad -bap -i4 $$i.e.c && gcc -o $$i.e $$i.e.c; done
