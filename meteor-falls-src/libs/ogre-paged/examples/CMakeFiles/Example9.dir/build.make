# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged

# Include any dependencies generated for this target.
include examples/CMakeFiles/Example9.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Example9.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Example9.dir/flags.make

examples/CMakeFiles/Example9.dir/Example9.o: examples/CMakeFiles/Example9.dir/flags.make
examples/CMakeFiles/Example9.dir/Example9.o: examples/Example9.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/Example9.dir/Example9.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Example9.dir/Example9.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example9.cpp

examples/CMakeFiles/Example9.dir/Example9.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Example9.dir/Example9.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example9.cpp > CMakeFiles/Example9.dir/Example9.i

examples/CMakeFiles/Example9.dir/Example9.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Example9.dir/Example9.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example9.cpp -o CMakeFiles/Example9.dir/Example9.s

examples/CMakeFiles/Example9.dir/Example9.o.requires:
.PHONY : examples/CMakeFiles/Example9.dir/Example9.o.requires

examples/CMakeFiles/Example9.dir/Example9.o.provides: examples/CMakeFiles/Example9.dir/Example9.o.requires
	$(MAKE) -f examples/CMakeFiles/Example9.dir/build.make examples/CMakeFiles/Example9.dir/Example9.o.provides.build
.PHONY : examples/CMakeFiles/Example9.dir/Example9.o.provides

examples/CMakeFiles/Example9.dir/Example9.o.provides.build: examples/CMakeFiles/Example9.dir/Example9.o

# Object files for target Example9
Example9_OBJECTS = \
"CMakeFiles/Example9.dir/Example9.o"

# External object files for target Example9
Example9_EXTERNAL_OBJECTS =

bin/Example9: examples/CMakeFiles/Example9.dir/Example9.o
bin/Example9: examples/CMakeFiles/Example9.dir/build.make
bin/Example9: lib/libPagedGeometry.a
bin/Example9: examples/CMakeFiles/Example9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/Example9"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Example9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Example9.dir/build: bin/Example9
.PHONY : examples/CMakeFiles/Example9.dir/build

examples/CMakeFiles/Example9.dir/requires: examples/CMakeFiles/Example9.dir/Example9.o.requires
.PHONY : examples/CMakeFiles/Example9.dir/requires

examples/CMakeFiles/Example9.dir/clean:
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && $(CMAKE_COMMAND) -P CMakeFiles/Example9.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Example9.dir/clean

examples/CMakeFiles/Example9.dir/depend:
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/CMakeFiles/Example9.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Example9.dir/depend

