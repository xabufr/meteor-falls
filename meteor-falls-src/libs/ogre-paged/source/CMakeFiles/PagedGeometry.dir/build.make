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
include source/CMakeFiles/PagedGeometry.dir/depend.make

# Include the progress variables for this target.
include source/CMakeFiles/PagedGeometry.dir/progress.make

# Include the compile flags for this target's objects.
include source/CMakeFiles/PagedGeometry.dir/flags.make

source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o: source/StaticBillboardSet.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/StaticBillboardSet.cpp

source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/StaticBillboardSet.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/StaticBillboardSet.cpp > CMakeFiles/PagedGeometry.dir/StaticBillboardSet.i

source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/StaticBillboardSet.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/StaticBillboardSet.cpp -o CMakeFiles/PagedGeometry.dir/StaticBillboardSet.s

source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.requires

source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.provides: source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.provides

source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.provides.build: source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o

source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o: source/WindBatchedGeometry.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/WindBatchedGeometry.cpp

source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/WindBatchedGeometry.cpp > CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.i

source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/WindBatchedGeometry.cpp -o CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.s

source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.requires

source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.provides: source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.provides

source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.provides.build: source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o

source/CMakeFiles/PagedGeometry.dir/BatchPage.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/BatchPage.o: source/BatchPage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/BatchPage.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/BatchPage.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/BatchPage.cpp

source/CMakeFiles/PagedGeometry.dir/BatchPage.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/BatchPage.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/BatchPage.cpp > CMakeFiles/PagedGeometry.dir/BatchPage.i

source/CMakeFiles/PagedGeometry.dir/BatchPage.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/BatchPage.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/BatchPage.cpp -o CMakeFiles/PagedGeometry.dir/BatchPage.s

source/CMakeFiles/PagedGeometry.dir/BatchPage.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/BatchPage.o.requires

source/CMakeFiles/PagedGeometry.dir/BatchPage.o.provides: source/CMakeFiles/PagedGeometry.dir/BatchPage.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/BatchPage.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/BatchPage.o.provides

source/CMakeFiles/PagedGeometry.dir/BatchPage.o.provides.build: source/CMakeFiles/PagedGeometry.dir/BatchPage.o

source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o: source/BatchedGeometry.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/BatchedGeometry.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/BatchedGeometry.cpp

source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/BatchedGeometry.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/BatchedGeometry.cpp > CMakeFiles/PagedGeometry.dir/BatchedGeometry.i

source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/BatchedGeometry.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/BatchedGeometry.cpp -o CMakeFiles/PagedGeometry.dir/BatchedGeometry.s

source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.requires

source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.provides: source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.provides

source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.provides.build: source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o

source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o: source/TreeLoader3D.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/TreeLoader3D.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/TreeLoader3D.cpp

source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/TreeLoader3D.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/TreeLoader3D.cpp > CMakeFiles/PagedGeometry.dir/TreeLoader3D.i

source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/TreeLoader3D.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/TreeLoader3D.cpp -o CMakeFiles/PagedGeometry.dir/TreeLoader3D.s

source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.requires

source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.provides: source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.provides

source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.provides.build: source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o

source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o: source/PropertyMaps.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/PropertyMaps.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/PropertyMaps.cpp

source/CMakeFiles/PagedGeometry.dir/PropertyMaps.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/PropertyMaps.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/PropertyMaps.cpp > CMakeFiles/PagedGeometry.dir/PropertyMaps.i

source/CMakeFiles/PagedGeometry.dir/PropertyMaps.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/PropertyMaps.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/PropertyMaps.cpp -o CMakeFiles/PagedGeometry.dir/PropertyMaps.s

source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.requires

source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.provides: source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.provides

source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.provides.build: source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o

source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o: source/ImpostorPage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/ImpostorPage.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/ImpostorPage.cpp

source/CMakeFiles/PagedGeometry.dir/ImpostorPage.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/ImpostorPage.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/ImpostorPage.cpp > CMakeFiles/PagedGeometry.dir/ImpostorPage.i

source/CMakeFiles/PagedGeometry.dir/ImpostorPage.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/ImpostorPage.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/ImpostorPage.cpp -o CMakeFiles/PagedGeometry.dir/ImpostorPage.s

source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.requires

source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.provides: source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.provides

source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.provides.build: source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o

source/CMakeFiles/PagedGeometry.dir/GrassLoader.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/GrassLoader.o: source/GrassLoader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/GrassLoader.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/GrassLoader.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/GrassLoader.cpp

source/CMakeFiles/PagedGeometry.dir/GrassLoader.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/GrassLoader.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/GrassLoader.cpp > CMakeFiles/PagedGeometry.dir/GrassLoader.i

source/CMakeFiles/PagedGeometry.dir/GrassLoader.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/GrassLoader.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/GrassLoader.cpp -o CMakeFiles/PagedGeometry.dir/GrassLoader.s

source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.requires

source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.provides: source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.provides

source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.provides.build: source/CMakeFiles/PagedGeometry.dir/GrassLoader.o

source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o: source/TreeLoader2D.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/TreeLoader2D.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/TreeLoader2D.cpp

source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/TreeLoader2D.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/TreeLoader2D.cpp > CMakeFiles/PagedGeometry.dir/TreeLoader2D.i

source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/TreeLoader2D.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/TreeLoader2D.cpp -o CMakeFiles/PagedGeometry.dir/TreeLoader2D.s

source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.requires

source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.provides: source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.provides

source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.provides.build: source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o

source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o: source/PagedGeometry.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/PagedGeometry.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/PagedGeometry.cpp

source/CMakeFiles/PagedGeometry.dir/PagedGeometry.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/PagedGeometry.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/PagedGeometry.cpp > CMakeFiles/PagedGeometry.dir/PagedGeometry.i

source/CMakeFiles/PagedGeometry.dir/PagedGeometry.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/PagedGeometry.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/PagedGeometry.cpp -o CMakeFiles/PagedGeometry.dir/PagedGeometry.s

source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.requires

source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.provides: source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.provides

source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.provides.build: source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o

source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o: source/CMakeFiles/PagedGeometry.dir/flags.make
source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o: source/WindBatchPage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagedGeometry.dir/WindBatchPage.o -c /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/WindBatchPage.cpp

source/CMakeFiles/PagedGeometry.dir/WindBatchPage.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagedGeometry.dir/WindBatchPage.i"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/WindBatchPage.cpp > CMakeFiles/PagedGeometry.dir/WindBatchPage.i

source/CMakeFiles/PagedGeometry.dir/WindBatchPage.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagedGeometry.dir/WindBatchPage.s"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/WindBatchPage.cpp -o CMakeFiles/PagedGeometry.dir/WindBatchPage.s

source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.requires:
.PHONY : source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.requires

source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.provides: source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.requires
	$(MAKE) -f source/CMakeFiles/PagedGeometry.dir/build.make source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.provides.build
.PHONY : source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.provides

source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.provides.build: source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o

# Object files for target PagedGeometry
PagedGeometry_OBJECTS = \
"CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o" \
"CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o" \
"CMakeFiles/PagedGeometry.dir/BatchPage.o" \
"CMakeFiles/PagedGeometry.dir/BatchedGeometry.o" \
"CMakeFiles/PagedGeometry.dir/TreeLoader3D.o" \
"CMakeFiles/PagedGeometry.dir/PropertyMaps.o" \
"CMakeFiles/PagedGeometry.dir/ImpostorPage.o" \
"CMakeFiles/PagedGeometry.dir/GrassLoader.o" \
"CMakeFiles/PagedGeometry.dir/TreeLoader2D.o" \
"CMakeFiles/PagedGeometry.dir/PagedGeometry.o" \
"CMakeFiles/PagedGeometry.dir/WindBatchPage.o"

# External object files for target PagedGeometry
PagedGeometry_EXTERNAL_OBJECTS =

lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/BatchPage.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/GrassLoader.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/build.make
lib/libPagedGeometry.a: source/CMakeFiles/PagedGeometry.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../lib/libPagedGeometry.a"
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && $(CMAKE_COMMAND) -P CMakeFiles/PagedGeometry.dir/cmake_clean_target.cmake
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PagedGeometry.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/CMakeFiles/PagedGeometry.dir/build: lib/libPagedGeometry.a
.PHONY : source/CMakeFiles/PagedGeometry.dir/build

source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/StaticBillboardSet.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/WindBatchedGeometry.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/BatchPage.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/BatchedGeometry.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/TreeLoader3D.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/PropertyMaps.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/ImpostorPage.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/GrassLoader.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/TreeLoader2D.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/PagedGeometry.o.requires
source/CMakeFiles/PagedGeometry.dir/requires: source/CMakeFiles/PagedGeometry.dir/WindBatchPage.o.requires
.PHONY : source/CMakeFiles/PagedGeometry.dir/requires

source/CMakeFiles/PagedGeometry.dir/clean:
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source && $(CMAKE_COMMAND) -P CMakeFiles/PagedGeometry.dir/cmake_clean.cmake
.PHONY : source/CMakeFiles/PagedGeometry.dir/clean

source/CMakeFiles/PagedGeometry.dir/depend:
	cd /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source /home/zequiel/software/c++/meteor-falls/meteor-falls-src/libs/ogre-paged/source/CMakeFiles/PagedGeometry.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/CMakeFiles/PagedGeometry.dir/depend

