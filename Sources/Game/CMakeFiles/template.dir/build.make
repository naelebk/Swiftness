# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game"

# Include any dependencies generated for this target.
include CMakeFiles/template.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/template.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/template.dir/flags.make

CMakeFiles/template.dir/gameTemplate.cc.o: CMakeFiles/template.dir/flags.make
CMakeFiles/template.dir/gameTemplate.cc.o: gameTemplate.cc
CMakeFiles/template.dir/gameTemplate.cc.o: CMakeFiles/template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/template.dir/gameTemplate.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/template.dir/gameTemplate.cc.o -MF CMakeFiles/template.dir/gameTemplate.cc.o.d -o CMakeFiles/template.dir/gameTemplate.cc.o -c "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game/gameTemplate.cc"

CMakeFiles/template.dir/gameTemplate.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template.dir/gameTemplate.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game/gameTemplate.cc" > CMakeFiles/template.dir/gameTemplate.cc.i

CMakeFiles/template.dir/gameTemplate.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template.dir/gameTemplate.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game/gameTemplate.cc" -o CMakeFiles/template.dir/gameTemplate.cc.s

# Object files for target template
template_OBJECTS = \
"CMakeFiles/template.dir/gameTemplate.cc.o"

# External object files for target template
template_EXTERNAL_OBJECTS =

template: CMakeFiles/template.dir/gameTemplate.cc.o
template: CMakeFiles/template.dir/build.make
template: /usr/local/lib/libgf0.so.1.2.0
template: /usr/local/lib/libgfnet0.so.1.2.0
template: /usr/local/lib/libgfcore0.so.1.2.0
template: /usr/lib/x86_64-linux-gnu/libz.so
template: CMakeFiles/template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable template"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/template.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/template.dir/build: template
.PHONY : CMakeFiles/template.dir/build

CMakeFiles/template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/template.dir/cmake_clean.cmake
.PHONY : CMakeFiles/template.dir/clean

CMakeFiles/template.dir/depend:
	cd "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game" "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game" "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game" "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game" "/mnt/76328C97328C5E4D/Naël PERSO/Cours Informatique/PROJET_LICENCE/Swiftness/Sources/Game/CMakeFiles/template.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/template.dir/depend

