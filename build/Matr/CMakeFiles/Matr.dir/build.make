# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vlad/Desktop/VSCode/Test1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vlad/Desktop/VSCode/Test1/build

# Include any dependencies generated for this target.
include Matr/CMakeFiles/Matr.dir/depend.make

# Include the progress variables for this target.
include Matr/CMakeFiles/Matr.dir/progress.make

# Include the compile flags for this target's objects.
include Matr/CMakeFiles/Matr.dir/flags.make

Matr/CMakeFiles/Matr.dir/matr.cpp.o: Matr/CMakeFiles/Matr.dir/flags.make
Matr/CMakeFiles/Matr.dir/matr.cpp.o: ../Matr/matr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vlad/Desktop/VSCode/Test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Matr/CMakeFiles/Matr.dir/matr.cpp.o"
	cd /Users/vlad/Desktop/VSCode/Test1/build/Matr && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Matr.dir/matr.cpp.o -c /Users/vlad/Desktop/VSCode/Test1/Matr/matr.cpp

Matr/CMakeFiles/Matr.dir/matr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Matr.dir/matr.cpp.i"
	cd /Users/vlad/Desktop/VSCode/Test1/build/Matr && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vlad/Desktop/VSCode/Test1/Matr/matr.cpp > CMakeFiles/Matr.dir/matr.cpp.i

Matr/CMakeFiles/Matr.dir/matr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Matr.dir/matr.cpp.s"
	cd /Users/vlad/Desktop/VSCode/Test1/build/Matr && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vlad/Desktop/VSCode/Test1/Matr/matr.cpp -o CMakeFiles/Matr.dir/matr.cpp.s

# Object files for target Matr
Matr_OBJECTS = \
"CMakeFiles/Matr.dir/matr.cpp.o"

# External object files for target Matr
Matr_EXTERNAL_OBJECTS =

Matr/libMatr.a: Matr/CMakeFiles/Matr.dir/matr.cpp.o
Matr/libMatr.a: Matr/CMakeFiles/Matr.dir/build.make
Matr/libMatr.a: Matr/CMakeFiles/Matr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vlad/Desktop/VSCode/Test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libMatr.a"
	cd /Users/vlad/Desktop/VSCode/Test1/build/Matr && $(CMAKE_COMMAND) -P CMakeFiles/Matr.dir/cmake_clean_target.cmake
	cd /Users/vlad/Desktop/VSCode/Test1/build/Matr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Matr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Matr/CMakeFiles/Matr.dir/build: Matr/libMatr.a

.PHONY : Matr/CMakeFiles/Matr.dir/build

Matr/CMakeFiles/Matr.dir/clean:
	cd /Users/vlad/Desktop/VSCode/Test1/build/Matr && $(CMAKE_COMMAND) -P CMakeFiles/Matr.dir/cmake_clean.cmake
.PHONY : Matr/CMakeFiles/Matr.dir/clean

Matr/CMakeFiles/Matr.dir/depend:
	cd /Users/vlad/Desktop/VSCode/Test1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vlad/Desktop/VSCode/Test1 /Users/vlad/Desktop/VSCode/Test1/Matr /Users/vlad/Desktop/VSCode/Test1/build /Users/vlad/Desktop/VSCode/Test1/build/Matr /Users/vlad/Desktop/VSCode/Test1/build/Matr/CMakeFiles/Matr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Matr/CMakeFiles/Matr.dir/depend

