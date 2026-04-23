# CMakeLists.txt

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Nelta VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(SDL2 REQUIRED)

# Set include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${Qt6_INCLUDE_DIRS})

# Add melonDS integration (assuming melonDS is available as a submodule)
add_subdirectory(melonDS)

# Source files
set(SOURCES
    main.cpp
    # Add other source files here
)

# Create executable target
add_executable(Nelta ${SOURCES})

# Link libraries
target_link_libraries(Nelta Qt6::Core Qt6::Gui Qt6::Widgets SDL2::SDL2 melonDS)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Install target
install(TARGETS Nelta DESTINATION bin)