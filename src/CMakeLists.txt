set(LIB_SOURCES cgException.c cgAppState.c cgLogger.c cgInteger.c
    cgString.c lookup3.c cgRectangle.c)
set(INSTALL_HEADERS
    "cgAppState.h;cgArray.h;cgArrayIterator.h;cgException.h;cgHashMap.h;cgInteger.h;cgKVPair.h;cgLinkedList.h;cgLogger.h;cgString.h;cgTree.h;cgRectangle.h;cgenerics.h")

add_library(cgenerics STATIC ${LIB_SOURCES})
link_directories(${CGENERICS_BIN_DIRECTORIES}/cgenerics)

INCLUDE (CheckIncludeFiles)

# usage: CHECK_INCLUDE_FILES (<header> <RESULT_VARIABLE> )
CHECK_INCLUDE_FILES ("malloc.h" HAVE_MALLOC_H)
CHECK_INCLUDE_FILES ("stdlib.h" HAVE_STDLIB_H)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

install(TARGETS cgenerics ARCHIVE DESTINATION lib/)
install(FILES ${INSTALL_HEADERS}
    DESTINATION include/cgenerics)

