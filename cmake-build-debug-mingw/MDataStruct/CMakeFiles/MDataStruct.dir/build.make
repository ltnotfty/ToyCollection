# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = D:/Clion_All/CLion-2022.2.4/bin/cmake/win/bin/cmake.exe

# The command to remove a file.
RM = D:/Clion_All/CLion-2022.2.4/bin/cmake/win/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/Project/TestMe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/Project/TestMe/cmake-build-debug-mingw

# Include any dependencies generated for this target.
include MDataStruct/CMakeFiles/MDataStruct.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include MDataStruct/CMakeFiles/MDataStruct.dir/compiler_depend.make

# Include the progress variables for this target.
include MDataStruct/CMakeFiles/MDataStruct.dir/progress.make

# Include the compile flags for this target's objects.
include MDataStruct/CMakeFiles/MDataStruct.dir/flags.make

MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.obj: MDataStruct/CMakeFiles/MDataStruct.dir/flags.make
MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.obj: MDataStruct/CMakeFiles/MDataStruct.dir/includes_CXX.rsp
MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.obj: ../MDataStruct/FixStr.cpp
MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.obj: MDataStruct/CMakeFiles/MDataStruct.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Project/TestMe/cmake-build-debug-mingw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.obj"
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && D:/Cygwin/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.obj -MF CMakeFiles/MDataStruct.dir/FixStr.cpp.obj.d -o CMakeFiles/MDataStruct.dir/FixStr.cpp.obj -c D:/Project/TestMe/MDataStruct/FixStr.cpp

MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MDataStruct.dir/FixStr.cpp.i"
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && D:/Cygwin/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Project/TestMe/MDataStruct/FixStr.cpp > CMakeFiles/MDataStruct.dir/FixStr.cpp.i

MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MDataStruct.dir/FixStr.cpp.s"
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && D:/Cygwin/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Project/TestMe/MDataStruct/FixStr.cpp -o CMakeFiles/MDataStruct.dir/FixStr.cpp.s

MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj: MDataStruct/CMakeFiles/MDataStruct.dir/flags.make
MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj: MDataStruct/CMakeFiles/MDataStruct.dir/includes_CXX.rsp
MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj: ../MDataStruct/MDataStruct.cpp
MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj: MDataStruct/CMakeFiles/MDataStruct.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Project/TestMe/cmake-build-debug-mingw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj"
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && D:/Cygwin/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj -MF CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj.d -o CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj -c D:/Project/TestMe/MDataStruct/MDataStruct.cpp

MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MDataStruct.dir/MDataStruct.cpp.i"
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && D:/Cygwin/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Project/TestMe/MDataStruct/MDataStruct.cpp > CMakeFiles/MDataStruct.dir/MDataStruct.cpp.i

MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MDataStruct.dir/MDataStruct.cpp.s"
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && D:/Cygwin/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Project/TestMe/MDataStruct/MDataStruct.cpp -o CMakeFiles/MDataStruct.dir/MDataStruct.cpp.s

# Object files for target MDataStruct
MDataStruct_OBJECTS = \
"CMakeFiles/MDataStruct.dir/FixStr.cpp.obj" \
"CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj"

# External object files for target MDataStruct
MDataStruct_EXTERNAL_OBJECTS =

MDataStruct/libMDataStruct.a: MDataStruct/CMakeFiles/MDataStruct.dir/FixStr.cpp.obj
MDataStruct/libMDataStruct.a: MDataStruct/CMakeFiles/MDataStruct.dir/MDataStruct.cpp.obj
MDataStruct/libMDataStruct.a: MDataStruct/CMakeFiles/MDataStruct.dir/build.make
MDataStruct/libMDataStruct.a: MDataStruct/CMakeFiles/MDataStruct.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Project/TestMe/cmake-build-debug-mingw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libMDataStruct.a"
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && $(CMAKE_COMMAND) -P CMakeFiles/MDataStruct.dir/cmake_clean_target.cmake
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MDataStruct.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MDataStruct/CMakeFiles/MDataStruct.dir/build: MDataStruct/libMDataStruct.a
.PHONY : MDataStruct/CMakeFiles/MDataStruct.dir/build

MDataStruct/CMakeFiles/MDataStruct.dir/clean:
	cd D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct && $(CMAKE_COMMAND) -P CMakeFiles/MDataStruct.dir/cmake_clean.cmake
.PHONY : MDataStruct/CMakeFiles/MDataStruct.dir/clean

MDataStruct/CMakeFiles/MDataStruct.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Project/TestMe D:/Project/TestMe/MDataStruct D:/Project/TestMe/cmake-build-debug-mingw D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct D:/Project/TestMe/cmake-build-debug-mingw/MDataStruct/CMakeFiles/MDataStruct.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MDataStruct/CMakeFiles/MDataStruct.dir/depend
