set(LIB_SOURCES CGException.c CGAppState.c CGLogger.c CGInteger.c CGString.c lookup3.c)

add_library(cgenerics STATIC ${LIB_SOURCES})
link_directories(${CGENERICS_BIN_DIRECTORIES}/cgenerics)
