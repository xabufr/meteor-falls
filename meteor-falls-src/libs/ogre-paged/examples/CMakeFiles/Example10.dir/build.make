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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged

# Include any dependencies generated for this target.
include examples/CMakeFiles/Example10.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Example10.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Example10.dir/flags.make

examples/CMakeFiles/Example10.dir/Example10.o: examples/CMakeFiles/Example10.dir/flags.make
examples/CMakeFiles/Example10.dir/Example10.o: examples/Example10.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/Example10.dir/Example10.o"
	cd /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Example10.dir/Example10.o -c /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example10.cpp

examples/CMakeFiles/Example10.dir/Example10.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Example10.dir/Example10.i"
	cd /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example10.cpp > CMakeFiles/Example10.dir/Example10.i

examples/CMakeFiles/Example10.dir/Example10.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Example10.dir/Example10.s"
	cd /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example10.cpp -o CMakeFiles/Example10.dir/Example10.s

examples/CMakeFiles/Example10.dir/Example10.o.requires:
.PHONY : examples/CMakeFiles/Example10.dir/Example10.o.requires

examples/CMakeFiles/Example10.dir/Example10.o.provides: examples/CMakeFiles/Example10.dir/Example10.o.requires
	$(MAKE) -f examples/CMakeFiles/Example10.dir/build.make examples/CMakeFiles/Example10.dir/Example10.o.provides.build
.PHONY : examples/CMakeFiles/Example10.dir/Example10.o.provides

examples/CMakeFiles/Example10.dir/Example10.o.provides.build: examples/CMakeFiles/Example10.dir/Example10.o

# Object files for target Example10
Example10_OBJECTS = \
"CMakeFiles/Example10.dir/Example10.o"

# External object files for target Example10
Example10_EXTERNAL_OBJECTS =

bin/Example10: examples/CMakeFiles/Example10.dir/Example10.o
bin/Example10: lib/libPagedGeometry.a
bin/Example10: examples/CMakeFiles/Example10.dir/build.make
bin/Example10: examples/CMakeFiles/Example10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/Example10"
	cd /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Example10.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Example10.dir/build: bin/Example10
.PHONY : examples/CMakeFiles/Example10.dir/build

examples/CMakeFiles/Example10.dir/requires: examples/CMakeFiles/Example10.dir/Example10.o.requires
.PHONY : examples/CMakeFiles/Example10.dir/requires

examples/CMakeFiles/Example10.dir/clean:
	cd /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && $(CMAKE_COMMAND) -P CMakeFiles/Example10.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Example10.dir/clean

examples/CMakeFiles/Example10.dir/depend:
	cd /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples /home/bastien/Bureau/Projet_CSII1/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/CMakeFiles/Example10.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Example10.dir/depend

