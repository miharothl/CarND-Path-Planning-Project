# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.8.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.8.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/miha/tmp/gtest_example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/miha/tmp/gtest_example

# Include any dependencies generated for this target.
include googletest-master/googletest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include googletest-master/googletest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include googletest-master/googletest/CMakeFiles/gtest.dir/flags.make

googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: googletest-master/googletest/CMakeFiles/gtest.dir/flags.make
googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: googletest-master/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/miha/tmp/gtest_example/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /Users/miha/tmp/gtest_example/googletest-master/googletest && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /Users/miha/tmp/gtest_example/googletest-master/googletest/src/gtest-all.cc

googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /Users/miha/tmp/gtest_example/googletest-master/googletest && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/miha/tmp/gtest_example/googletest-master/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /Users/miha/tmp/gtest_example/googletest-master/googletest && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/miha/tmp/gtest_example/googletest-master/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires:

.PHONY : googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides: googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires
	$(MAKE) -f googletest-master/googletest/CMakeFiles/gtest.dir/build.make googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build
.PHONY : googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides

googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build: googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o


# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

googletest-master/googletest/libgtest.a: googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
googletest-master/googletest/libgtest.a: googletest-master/googletest/CMakeFiles/gtest.dir/build.make
googletest-master/googletest/libgtest.a: googletest-master/googletest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/miha/tmp/gtest_example/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /Users/miha/tmp/gtest_example/googletest-master/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /Users/miha/tmp/gtest_example/googletest-master/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googletest-master/googletest/CMakeFiles/gtest.dir/build: googletest-master/googletest/libgtest.a

.PHONY : googletest-master/googletest/CMakeFiles/gtest.dir/build

googletest-master/googletest/CMakeFiles/gtest.dir/requires: googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

.PHONY : googletest-master/googletest/CMakeFiles/gtest.dir/requires

googletest-master/googletest/CMakeFiles/gtest.dir/clean:
	cd /Users/miha/tmp/gtest_example/googletest-master/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : googletest-master/googletest/CMakeFiles/gtest.dir/clean

googletest-master/googletest/CMakeFiles/gtest.dir/depend:
	cd /Users/miha/tmp/gtest_example && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/miha/tmp/gtest_example /Users/miha/tmp/gtest_example/googletest-master/googletest /Users/miha/tmp/gtest_example /Users/miha/tmp/gtest_example/googletest-master/googletest /Users/miha/tmp/gtest_example/googletest-master/googletest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : googletest-master/googletest/CMakeFiles/gtest.dir/depend

