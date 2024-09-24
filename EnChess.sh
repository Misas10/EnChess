#!/bin/sh

# Some useful colors
Color_Off='\033[0m'       # Text Reset

Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Blue='\033[0;34m'         # Blue

PROJECT_PATH="$PWD"
BUILD_PATH="$PROJECT_PATH/build/enchess_build"

Help() {
  echo "Usage: ./EnChess [option]"
  # echo
  echo "Systax: [-i|b|r]"
  echo "Options: "
  echo "-b            Only builds and doesn't run"
  echo "-r            Compile and run the app if exists"
  echo "-h, --help    Show this help info"
  echo
  echo "EnChess made by Misas"
}

Run(){
  echo -e "${Blue}Running Enchess...${Color_Off}"
  "$BUILD_PATH/EnChess"
}

CompileRun() {
  echo -e "${Blue}Running make${Color_Off}"
  make -f "$PROJECT_PATH/build/enchess_build/Makefile" $PROJECT_PATH
  Run
}

Build() {
  # Create the build file if it does not exists
  mkdir -p $BUILD_PATH

  echo -e "${Blue}Running cmake...${Color_Off}"
  cmake -S $PROJECT_PATH -B $BUILD_PATH

  echo -e "${Blue}Compiling...${Color_Off}"
  cmake --build $BUILD_PATH
}

# If no options are not selected try to run
if [ $# -eq 0 ]; then
 Run 
 exit
fi

while [[ $# -gt 0 ]]; do
  case $1 in
    -r) CompileRun
      exit;; 
    -b) Build
      exit;;
    -br) Build
      Run
      exit;;
    -h|--help) Help
      exit;;
    --)
      shift
      break
      ;;
    -*|--*)
      # echo "${0}: invalid option -- '${1}'"
      echo -e "${Red}Invalid option: '${1}' ${Color_off}"
      exit 1
      ;;
    *)
      positional_args+=("$1") # Save positional args
      shift
      ;;
  esac
done


# If getopt wasn't used
if [ -z "$_options" ]; then
  # Restore positional arguments
  set -- "${positional_args[@]}"
fi
