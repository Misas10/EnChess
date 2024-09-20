#!/bin/bash

# Some useful colors
Color_Off='\033[0m'       # Text Reset

Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Blue='\033[0;34m'         # Blue

PROJECT_PATH="$PWD"
BUILD_PATH="$PROJECT_PATH/build/enchess_build"

# Create the build file if it does not exists
mkdir -p $BUILD_PATH

# echo "$BUILD_PATH"

echo -e "${Blue}Running cmake...${Color_Off}"
cmake -S $PROJECT_PATH -B $BUILD_PATH

echo -e "${Blue}Compiling...${Color_Off}"
cmake --build $BUILD_PATH

echo -e "${Blue}Running Enchess...${Color_Off}"
"$BUILD_PATH/EnChess"
