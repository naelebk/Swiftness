# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/juliengauthier410/l3/s5/_PROJECT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/juliengauthier410/l3/s5/_PROJECT

# Include any dependencies generated for this target.
include CMakeFiles/foogame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/foogame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/foogame.dir/flags.make

CMakeFiles/foogame.dir/foogame.cc.o: CMakeFiles/foogame.dir/flags.make
CMakeFiles/foogame.dir/foogame.cc.o: foogame.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/juliengauthier410/l3/s5/_PROJECT/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/foogame.dir/foogame.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/foogame.dir/foogame.cc.o -c /home/juliengauthier410/l3/s5/_PROJECT/foogame.cc

CMakeFiles/foogame.dir/foogame.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/foogame.dir/foogame.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/juliengauthier410/l3/s5/_PROJECT/foogame.cc > CMakeFiles/foogame.dir/foogame.cc.i

CMakeFiles/foogame.dir/foogame.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/foogame.dir/foogame.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/juliengauthier410/l3/s5/_PROJECT/foogame.cc -o CMakeFiles/foogame.dir/foogame.cc.s

# Object files for target foogame
foogame_OBJECTS = \
"CMakeFiles/foogame.dir/foogame.cc.o"

# External object files for target foogame
foogame_EXTERNAL_OBJECTS =

foogame: CMakeFiles/foogame.dir/foogame.cc.o
foogame: CMakeFiles/foogame.dir/build.make
foogame: /usr/local/lib/libgf0.so.1.2.0
foogame: /usr/local/lib/libgfnet0.so.1.2.0
foogame: /usr/local/lib/libgfcore0.so.1.2.0
foogame: /usr/lib/x86_64-linux-gnu/libz.so
foogame: CMakeFiles/foogame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/juliengauthier410/l3/s5/_PROJECT/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable foogame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/foogame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/foogame.dir/build: foogame

.PHONY : CMakeFiles/foogame.dir/build

CMakeFiles/foogame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/foogame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/foogame.dir/clean

CMakeFiles/foogame.dir/depend:
	cd /home/juliengauthier410/l3/s5/_PROJECT && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/juliengauthier410/l3/s5/_PROJECT /home/juliengauthier410/l3/s5/_PROJECT /home/juliengauthier410/l3/s5/_PROJECT /home/juliengauthier410/l3/s5/_PROJECT /home/juliengauthier410/l3/s5/_PROJECT/CMakeFiles/foogame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/foogame.dir/depend

