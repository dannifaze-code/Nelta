cmake_minimum_required(VERSION 3.10)
project(Nelta VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 installed on the system
find_package(SDL2 REQUIRED)

# Include our source directories
include_directories(src)

# Add your melonDS include paths here (adjust based on your melonDS folder structure)
# include_directories(melonDs-master/src)

# Define all the source files we wrote
set(SOURCES
    src/main.cpp
    src/core/emulator_wrapper.cpp
    src/audio/audio_engine.cpp
    src/input/controller_manager.cpp
    src/ui/widgets/game_viewport.cpp
    src/cheats/cheat_manager.cpp
)

# Create the executable
add_executable(Nelta ${SOURCES})

# Link SDL2 to the executable
target_include_directories(Nelta PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Nelta PRIVATE ${SDL2_LIBRARIES})

# Link melonDS core library
# target_link_libraries(Nelta PRIVATE melonDS)
