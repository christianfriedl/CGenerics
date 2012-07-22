include Makefile.local
CFLAGS=-Wall -I../ -save-temps -ggdb
LDFLAGS=-Wall -L../ -lcgenerics -ggdb

BINARIES=0125_AppState 0250_Integer 0375_CGString 0500_Array 0510_ArrayIterator 0750_LinkedList 0800_CGTree 0900_KVPair 0950_HashMap
PERFORMANCE_BINARIES=0501_ArrayPerformance 
CURRENT_TEST_BINARY=0950_HashMap

clean-all: clean all

all: clean tests # performance

tests: $(BINARIES)

performance: $(PERFORMANCE_BINARIES)

clean:
	rm -f *.o *.e *.e.c *.BAK *.i *.s $(BINARIES) $(PERFORMANCE_BINARIES)
	rm -rf *.dSYM

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(CFLAGS)

pp:
	for i in $(BINARIES); do gcc $(CFLAGS) -E -o - -c $$i.c; done

pp-indent:
	for i in $(BINARIES); do gcc $(CFLAGS) -E -o $$i.e.c -c $$i.c && indent -bad -bap -i4 $$i.e.c && gcc -o $$i.e $$i.e.c; done

current: clean $(CURRENT_TEST_BINARY)
