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
CMAKE_SOURCE_DIR = /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged

# Include any dependencies generated for this target.
include examples/CMakeFiles/Example3.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Example3.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Example3.dir/flags.make

examples/CMakeFiles/Example3.dir/Example3.o: examples/CMakeFiles/Example3.dir/flags.make
examples/CMakeFiles/Example3.dir/Example3.o: examples/Example3.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/Example3.dir/Example3.o"
	cd /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Example3.dir/Example3.o -c /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example3.cpp

examples/CMakeFiles/Example3.dir/Example3.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Example3.dir/Example3.i"
	cd /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example3.cpp > CMakeFiles/Example3.dir/Example3.i

examples/CMakeFiles/Example3.dir/Example3.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Example3.dir/Example3.s"
	cd /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/Example3.cpp -o CMakeFiles/Example3.dir/Example3.s

examples/CMakeFiles/Example3.dir/Example3.o.requires:
.PHONY : examples/CMakeFiles/Example3.dir/Example3.o.requires

examples/CMakeFiles/Example3.dir/Example3.o.provides: examples/CMakeFiles/Example3.dir/Example3.o.requires
	$(MAKE) -f examples/CMakeFiles/Example3.dir/build.make examples/CMakeFiles/Example3.dir/Example3.o.provides.build
.PHONY : examples/CMakeFiles/Example3.dir/Example3.o.provides

examples/CMakeFiles/Example3.dir/Example3.o.provides.build: examples/CMakeFiles/Example3.dir/Example3.o

# Object files for target Example3
Example3_OBJECTS = \
"CMakeFiles/Example3.dir/Example3.o"

# External object files for target Example3
Example3_EXTERNAL_OBJECTS =

bin/Example3: examples/CMakeFiles/Example3.dir/Example3.o
bin/Example3: examples/CMakeFiles/Example3.dir/build.make
bin/Example3: lib/libPagedGeometry.a
bin/Example3: examples/CMakeFiles/Example3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/Example3"
	cd /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Example3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Example3.dir/build: bin/Example3
.PHONY : examples/CMakeFiles/Example3.dir/build

examples/CMakeFiles/Example3.dir/requires: examples/CMakeFiles/Example3.dir/Example3.o.requires
.PHONY : examples/CMakeFiles/Example3.dir/requires

examples/CMakeFiles/Example3.dir/clean:
	cd /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples && $(CMAKE_COMMAND) -P CMakeFiles/Example3.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Example3.dir/clean

examples/CMakeFiles/Example3.dir/depend:
	cd /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples /home/thomas/meteor-falls/meteor-falls-src/libs/ogre-paged/examples/CMakeFiles/Example3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Example3.dir/depend

