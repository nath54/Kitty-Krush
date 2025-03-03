#!/bin/bash

# Set the build directory
BUILD_DIR="build"

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${GREEN}Starting build process...${NC}"

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${GREEN}Creating build directory...${NC}"
    mkdir "$BUILD_DIR"
fi

# Navigate to the build directory
cd "$BUILD_DIR" || exit 1

# Run CMake
echo -e "${GREEN}Running CMake configuration...${NC}"
if ! cmake ..; then
    echo -e "${RED}CMake configuration failed!${NC}"
    exit 1
fi

# Compile the project
echo -e "${GREEN}Compiling the project...${NC}"
if ! cmake --build .; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi

# Return to project root
cd ..

# Success message
echo -e "${GREEN}Build completed successfully!${NC}"
echo -e "${GREEN}Executable is located in: ${BUILD_DIR}/bin/KittyKrush${NC}"
