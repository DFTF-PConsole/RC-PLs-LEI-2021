# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /cygdrive/c/Users/pcdar/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/pcdar/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Proj_Aux.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Proj_Aux.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Proj_Aux.dir/flags.make

CMakeFiles/Proj_Aux.dir/clienteTcp.c.o: CMakeFiles/Proj_Aux.dir/flags.make
CMakeFiles/Proj_Aux.dir/clienteTcp.c.o: ../clienteTcp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Proj_Aux.dir/clienteTcp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Proj_Aux.dir/clienteTcp.c.o -c "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/clienteTcp.c"

CMakeFiles/Proj_Aux.dir/clienteTcp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Proj_Aux.dir/clienteTcp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/clienteTcp.c" > CMakeFiles/Proj_Aux.dir/clienteTcp.c.i

CMakeFiles/Proj_Aux.dir/clienteTcp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Proj_Aux.dir/clienteTcp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/clienteTcp.c" -o CMakeFiles/Proj_Aux.dir/clienteTcp.c.s

# Object files for target Proj_Aux
Proj_Aux_OBJECTS = \
"CMakeFiles/Proj_Aux.dir/clienteTcp.c.o"

# External object files for target Proj_Aux
Proj_Aux_EXTERNAL_OBJECTS =

Proj_Aux.exe: CMakeFiles/Proj_Aux.dir/clienteTcp.c.o
Proj_Aux.exe: CMakeFiles/Proj_Aux.dir/build.make
Proj_Aux.exe: CMakeFiles/Proj_Aux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Proj_Aux.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Proj_Aux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Proj_Aux.dir/build: Proj_Aux.exe

.PHONY : CMakeFiles/Proj_Aux.dir/build

CMakeFiles/Proj_Aux.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Proj_Aux.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Proj_Aux.dir/clean

CMakeFiles/Proj_Aux.dir/depend:
	cd "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/cmake-build-debug" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/cmake-build-debug" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex1/Proj Aux/cmake-build-debug/CMakeFiles/Proj_Aux.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Proj_Aux.dir/depend
