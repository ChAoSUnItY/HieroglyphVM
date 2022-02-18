cmake_minimum_required(VERSION 3.13)  # CMake version check
project(HieroglyphVM)               # Create project "simple_example"

# Definitions
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
include_directories("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src")

# Add main.cpp file of project root directory as source file
file(GLOB SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(HieroglyphVM ${SOURCE})

