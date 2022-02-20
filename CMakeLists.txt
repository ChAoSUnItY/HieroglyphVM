cmake_minimum_required (VERSION 3.23)
project (HieroglyphVM)

set(CMAKE_C_FLAGS "-Wall -g")

file(GLOB SOURCES
    src/*.h
    src/*.c
)

add_executable(HieroglyphVM ${SOURCES})
