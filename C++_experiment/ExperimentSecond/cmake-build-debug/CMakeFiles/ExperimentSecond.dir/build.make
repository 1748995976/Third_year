# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CLion 2018.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CLion 2018.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Third_year\C++_experiment\ExperimentSecond

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Third_year\C++_experiment\ExperimentSecond\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ExperimentSecond.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ExperimentSecond.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ExperimentSecond.dir/flags.make

CMakeFiles/ExperimentSecond.dir/main.cpp.obj: CMakeFiles/ExperimentSecond.dir/flags.make
CMakeFiles/ExperimentSecond.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Third_year\C++_experiment\ExperimentSecond\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ExperimentSecond.dir/main.cpp.obj"
	C:\MinGW\bin\mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ExperimentSecond.dir\main.cpp.obj -c D:\Third_year\C++_experiment\ExperimentSecond\main.cpp

CMakeFiles/ExperimentSecond.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ExperimentSecond.dir/main.cpp.i"
	C:\MinGW\bin\mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Third_year\C++_experiment\ExperimentSecond\main.cpp > CMakeFiles\ExperimentSecond.dir\main.cpp.i

CMakeFiles/ExperimentSecond.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ExperimentSecond.dir/main.cpp.s"
	C:\MinGW\bin\mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Third_year\C++_experiment\ExperimentSecond\main.cpp -o CMakeFiles\ExperimentSecond.dir\main.cpp.s

CMakeFiles/ExperimentSecond.dir/stack.cpp.obj: CMakeFiles/ExperimentSecond.dir/flags.make
CMakeFiles/ExperimentSecond.dir/stack.cpp.obj: ../stack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Third_year\C++_experiment\ExperimentSecond\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ExperimentSecond.dir/stack.cpp.obj"
	C:\MinGW\bin\mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ExperimentSecond.dir\stack.cpp.obj -c D:\Third_year\C++_experiment\ExperimentSecond\stack.cpp

CMakeFiles/ExperimentSecond.dir/stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ExperimentSecond.dir/stack.cpp.i"
	C:\MinGW\bin\mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Third_year\C++_experiment\ExperimentSecond\stack.cpp > CMakeFiles\ExperimentSecond.dir\stack.cpp.i

CMakeFiles/ExperimentSecond.dir/stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ExperimentSecond.dir/stack.cpp.s"
	C:\MinGW\bin\mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Third_year\C++_experiment\ExperimentSecond\stack.cpp -o CMakeFiles\ExperimentSecond.dir\stack.cpp.s

# Object files for target ExperimentSecond
ExperimentSecond_OBJECTS = \
"CMakeFiles/ExperimentSecond.dir/main.cpp.obj" \
"CMakeFiles/ExperimentSecond.dir/stack.cpp.obj"

# External object files for target ExperimentSecond
ExperimentSecond_EXTERNAL_OBJECTS =

ExperimentSecond.exe: CMakeFiles/ExperimentSecond.dir/main.cpp.obj
ExperimentSecond.exe: CMakeFiles/ExperimentSecond.dir/stack.cpp.obj
ExperimentSecond.exe: CMakeFiles/ExperimentSecond.dir/build.make
ExperimentSecond.exe: CMakeFiles/ExperimentSecond.dir/linklibs.rsp
ExperimentSecond.exe: CMakeFiles/ExperimentSecond.dir/objects1.rsp
ExperimentSecond.exe: CMakeFiles/ExperimentSecond.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Third_year\C++_experiment\ExperimentSecond\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ExperimentSecond.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ExperimentSecond.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ExperimentSecond.dir/build: ExperimentSecond.exe

.PHONY : CMakeFiles/ExperimentSecond.dir/build

CMakeFiles/ExperimentSecond.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ExperimentSecond.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ExperimentSecond.dir/clean

CMakeFiles/ExperimentSecond.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Third_year\C++_experiment\ExperimentSecond D:\Third_year\C++_experiment\ExperimentSecond D:\Third_year\C++_experiment\ExperimentSecond\cmake-build-debug D:\Third_year\C++_experiment\ExperimentSecond\cmake-build-debug D:\Third_year\C++_experiment\ExperimentSecond\cmake-build-debug\CMakeFiles\ExperimentSecond.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ExperimentSecond.dir/depend
