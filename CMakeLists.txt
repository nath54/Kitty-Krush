cmake_minimum_required(VERSION 3.10)
project(TheGameProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

# Add the executable
add_executable(TheGame ${SOURCES} ${HEADERS})

# Optional: Add extra libraries (e.g., SFML, SDL, OpenGL)
# find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
# target_link_libraries(TheGame PRIVATE sfml-graphics sfml-window sfml-system)

# Set the output directory for the compiled binary
set_target_properties(TheGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Optional: Copy resources to the build directory
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/bin/res
)
add_dependencies(TheGame copy_resources)