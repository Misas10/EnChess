#!/bin/bash

# Some useful colors
Color_Off='\033[0m'       # Text Reset

Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Blue='\033[0;34m'         # Blue

CMAKE_PATH="build/enchess_build"

echo -e "${Blue}Running cmake...${Color_Off}"
cmake "$CMAKE_PATH/"

echo -e "${Blue}Compiling...${Color_Off}"
cmake --build "$CMAKE_PATH/"

echo -e "${Blue}Running Enchess...${Color_Off}"
"./$CMAKE_PATH/EnChess"
