# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/misael/Programming/c/EnChess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/misael/Programming/c/EnChess/build

# Include any dependencies generated for this target.
include CMakeFiles/EnChess.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/EnChess.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/EnChess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EnChess.dir/flags.make

CMakeFiles/EnChess.dir/src/main.c.o: CMakeFiles/EnChess.dir/flags.make
CMakeFiles/EnChess.dir/src/main.c.o: /Users/misael/Programming/c/EnChess/src/main.c
CMakeFiles/EnChess.dir/src/main.c.o: CMakeFiles/EnChess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/misael/Programming/c/EnChess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/EnChess.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/EnChess.dir/src/main.c.o -MF CMakeFiles/EnChess.dir/src/main.c.o.d -o CMakeFiles/EnChess.dir/src/main.c.o -c /Users/misael/Programming/c/EnChess/src/main.c

CMakeFiles/EnChess.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/EnChess.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/misael/Programming/c/EnChess/src/main.c > CMakeFiles/EnChess.dir/src/main.c.i

CMakeFiles/EnChess.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/EnChess.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/misael/Programming/c/EnChess/src/main.c -o CMakeFiles/EnChess.dir/src/main.c.s

# Object files for target EnChess
EnChess_OBJECTS = \
"CMakeFiles/EnChess.dir/src/main.c.o"

# External object files for target EnChess
EnChess_EXTERNAL_OBJECTS =

EnChess: CMakeFiles/EnChess.dir/src/main.c.o
EnChess: CMakeFiles/EnChess.dir/build.make
EnChess: CMakeFiles/EnChess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/misael/Programming/c/EnChess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable EnChess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EnChess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EnChess.dir/build: EnChess
.PHONY : CMakeFiles/EnChess.dir/build

CMakeFiles/EnChess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EnChess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EnChess.dir/clean

CMakeFiles/EnChess.dir/depend:
	cd /Users/misael/Programming/c/EnChess/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/misael/Programming/c/EnChess /Users/misael/Programming/c/EnChess /Users/misael/Programming/c/EnChess/build /Users/misael/Programming/c/EnChess/build /Users/misael/Programming/c/EnChess/build/CMakeFiles/EnChess.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/EnChess.dir/depend

