# CMake file for PixelMaestro unit tests
project (PixelMaestro_Test)
cmake_minimum_required(VERSION 3.6.2)

# Export project files to bin folder.
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Bring in local header and source files
#include_directories("../src" "../src/show")
file(GLOB_RECURSE SOURCES "tests/*.cpp" "tests/*.h" "../src/*.cpp" "../src/*.h")

# Add Catch header files
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "catch")

# Compile to bin/PixelMaestro_Test
add_executable(PixelMaestro_Test ${SOURCES})

# Add Catch as dependency
target_link_libraries(PixelMaestro_Test Catch)
