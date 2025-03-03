cmake_minimum_required(VERSION 3.10)
project(TheGame)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Threads REQUIRED)

# Include directories
include_directories(/usr/include include)

# Collect all source and header files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

# Add the executable
add_executable(TheGame ${SOURCES} ${HEADERS})

# Link SDL2
target_link_libraries(TheGame PRIVATE SDL2 SDL2_ttf)
target_link_libraries(TheGame PRIVATE ${SDL2_LIBRARIES})

# Set the output directory for the binary
set_target_properties(TheGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy resources to the build directory
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/bin/res
)
add_dependencies(TheGame copy_resources)
