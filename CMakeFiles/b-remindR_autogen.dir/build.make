# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/radu/dev/QT/b-remindR

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/radu/dev/QT/b-remindR

# Utility rule file for b-remindR_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/b-remindR_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/b-remindR_autogen.dir/progress.make

CMakeFiles/b-remindR_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/radu/dev/QT/b-remindR/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target b-remindR"
	/usr/bin/cmake -E cmake_autogen /home/radu/dev/QT/b-remindR/CMakeFiles/b-remindR_autogen.dir/AutogenInfo.json ""

b-remindR_autogen: CMakeFiles/b-remindR_autogen
b-remindR_autogen: CMakeFiles/b-remindR_autogen.dir/build.make
.PHONY : b-remindR_autogen

# Rule to build all files generated by this target.
CMakeFiles/b-remindR_autogen.dir/build: b-remindR_autogen
.PHONY : CMakeFiles/b-remindR_autogen.dir/build

CMakeFiles/b-remindR_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/b-remindR_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/b-remindR_autogen.dir/clean

CMakeFiles/b-remindR_autogen.dir/depend:
	cd /home/radu/dev/QT/b-remindR && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/radu/dev/QT/b-remindR /home/radu/dev/QT/b-remindR /home/radu/dev/QT/b-remindR /home/radu/dev/QT/b-remindR /home/radu/dev/QT/b-remindR/CMakeFiles/b-remindR_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/b-remindR_autogen.dir/depend

