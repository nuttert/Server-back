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
include CMakeFiles/Lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lib.dir/flags.make

CMakeFiles/Lib.dir/Matr/matr.cpp.o: CMakeFiles/Lib.dir/flags.make
CMakeFiles/Lib.dir/Matr/matr.cpp.o: ../Matr/matr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vlad/Desktop/VSCode/Test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lib.dir/Matr/matr.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lib.dir/Matr/matr.cpp.o -c /Users/vlad/Desktop/VSCode/Test1/Matr/matr.cpp

CMakeFiles/Lib.dir/Matr/matr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lib.dir/Matr/matr.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vlad/Desktop/VSCode/Test1/Matr/matr.cpp > CMakeFiles/Lib.dir/Matr/matr.cpp.i

CMakeFiles/Lib.dir/Matr/matr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lib.dir/Matr/matr.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vlad/Desktop/VSCode/Test1/Matr/matr.cpp -o CMakeFiles/Lib.dir/Matr/matr.cpp.s

# Object files for target Lib
Lib_OBJECTS = \
"CMakeFiles/Lib.dir/Matr/matr.cpp.o"

# External object files for target Lib
Lib_EXTERNAL_OBJECTS =

libLib.a: CMakeFiles/Lib.dir/Matr/matr.cpp.o
libLib.a: CMakeFiles/Lib.dir/build.make
libLib.a: CMakeFiles/Lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vlad/Desktop/VSCode/Test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libLib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lib.dir/build: libLib.a

.PHONY : CMakeFiles/Lib.dir/build

CMakeFiles/Lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lib.dir/clean

CMakeFiles/Lib.dir/depend:
	cd /Users/vlad/Desktop/VSCode/Test1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vlad/Desktop/VSCode/Test1 /Users/vlad/Desktop/VSCode/Test1 /Users/vlad/Desktop/VSCode/Test1/build /Users/vlad/Desktop/VSCode/Test1/build /Users/vlad/Desktop/VSCode/Test1/build/CMakeFiles/Lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lib.dir/depend

