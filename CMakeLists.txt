cmake_minimum_required (VERSION 2.8)
project (CGenerics)
# The version number.
set (CGenerics_VERSION_MAJOR 0)
set (CGenerics_VERSION_MINOR 5)


enable_testing()

if (CMAKE_COMPILER_IS_GNUCXX)
    set(NORMAL_WARNINGS -Wall)
    set(MEGA_WARNINGS "${USEFUL_WARNINGS} -Wredundant-decls -Wshadow -Wcast-align -Wwrite-strings -Winline -Wformat-nonliteral -Wformat-security -Wswitch -Wswitch-default -Winit-self -Wmissing-include-dirs -Wundef -Waggregate-return -Wmissing-format-attribute -Wnested-externs ")
    set(MEGA_WARNINGS "${INTENSIVE_WARNINGS} -Wdeclaration-after-statement -Wredundant-decls -Wmissing-noreturn -Wshadow -Wcast-align -Wwrite-strings -Winline -Wformat-nonliteral -Wformat-security -Wswitch -Wswitch-default -Winit-self -Wmissing-include-dirs -Wundef -Waggregate-return -Wmissing-format-attribute -Wnested-externs ")
    set(PARANOID_WARNINGS "${INTENSIVE_WARNINGS} -Werror")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USEFUL_WARNINGS}")
endif() 

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/config.h.in"
#  "${PROJECT_BINARY_DIR}/config.h"
#  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
add_subdirectory("src")
add_subdirectory("test")

set(CMAKE_INSTALL_PREFIX "/usr")
