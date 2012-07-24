set(LIB_SOURCES CGException.c CGAppState.c CGLogger.c CGInteger.c CGString.c lookup3.c)

add_library(cgenerics STATIC ${LIB_SOURCES})
link_directories(${CGENERICS_BIN_DIRECTORIES}/cgenerics)

INCLUDE (CheckIncludeFiles)

# usage: CHECK_INCLUDE_FILES (<header> <RESULT_VARIABLE> )
CHECK_INCLUDE_FILES ("malloc.h" HAVE_MALLOC_H)
CHECK_INCLUDE_FILES ("stdlib.h" HAVE_STDLIB_H)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
