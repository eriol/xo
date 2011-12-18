# Top-level CMakeLists.txt for xo

cmake_minimum_required(VERSION 2.8)

find_program(COLORGCC_EXECUTABLE colorgcc)

set(CMAKE_C_COMPILER "colorgcc")

project(xo C)

# Prevent build in source directory
if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message (FATAL_ERROR "Building in the source directory is not supported.")
endif ()

include_directories(src)

add_definitions(-Wall -W -Wextra -Wstrict-prototypes -pedantic -ansi -std=gnu99)

add_subdirectory(src)
