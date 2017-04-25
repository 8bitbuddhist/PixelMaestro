# CMake file for PixelMaestro GUI
project (PixelMaestro_GUI)
cmake_minimum_required(VERSION 3.6.2)

# Export project files to bin/Release.
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/Release)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Bring in local header and source files
include_directories("include" "include/drawingareas" "../include")
file(GLOB SOURCES "src/*.cpp" "src/drawingareas/*.cpp" "../src/*.cpp")

# Find and include GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# Compile to PixelMaestro_GUI.sh, .exe, etc.
add_executable(PixelMaestro_GUI ${SOURCES})

# Link the target to GTK
target_link_libraries(PixelMaestro_GUI ${GTKMM_LIBRARIES})
