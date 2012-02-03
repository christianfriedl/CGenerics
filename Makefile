include Makefile.local
NORMAL_WARNINGS = -Wall
MEGA_WARNINGS = -Wall -Wdeclaration-after-statement \
	-Wredundant-decls -Wmissing-noreturn -Wshadow -Wcast-align \
	-Wwrite-strings -Winline -Wformat-nonliteral -Wformat-security \
	-Wswitch -Wswitch-default -Winit-self -Wmissing-include-dirs \
	-Wundef -Waggregate-return -Wmissing-format-attribute \
	-Wnested-externs -Werror
WARNINGS = $(NORMAL_WARNINGS)
CFLAGS=-ggdb $(WARNINGS)
LDFLAGS=-ggdb $(WARNINGS) 

HEADERS=CGAppState.h CGArray.h CGException.h CGInteger.h CGLinkedList.h CGLogger.h CGString.h CGenerics.h
LIB_OBJECTS=CGException.o CGAppState.o CGLogger.o CGInteger.o CGString.o
STATIC_LIBRARY=libcgenerics.a

PREFIX=/usr
INSTALLHEADERS=${PREFIX}/include/cgenerics
INSTALLLIB=${PREFIX}/lib

clean-tests: clean tests test

necessary-tests: tests test

clean-all-test: clean all test

all-test: all test

pp:
	(cd test; make pp)

pp-indent:
	(cd test; make pp-indent)

tests: localall
	(cd test; make tests)

localall: $(STATIC_LIBRARY)

all: localall
	(cd test; make all)

$(STATIC_LIBRARY): $(LIB_OBJECTS)
	ar -rcsv $@ $?

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

clean:
	rm -f *.o $(TEST_BINARIES) $(STATIC_LIBRARY)
	(cd test; make clean)

.PHONY: test
test:
	for i in `find test -type f -not -name "*.*" -name "0*" |sort -n`; do $$i; if [ $$? != 0 ]; then echo "ERROR..."; exit 1; fi; done

install:
	if [ ! -d ${INSTALLHEADERS} ]; then mkdir -p ${INSTALLHEADERS}; fi
	cp $(HEADERS) ${INSTALLHEADERS}
	cp $(STATIC_LIBRARY) $(INSTALLLIB)
