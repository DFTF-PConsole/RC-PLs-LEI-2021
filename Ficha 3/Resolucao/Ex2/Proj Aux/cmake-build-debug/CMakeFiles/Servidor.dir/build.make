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
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Servidor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Servidor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Servidor.dir/flags.make

CMakeFiles/Servidor.dir/servidor.c.o: CMakeFiles/Servidor.dir/flags.make
CMakeFiles/Servidor.dir/servidor.c.o: ../servidor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Servidor.dir/servidor.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Servidor.dir/servidor.c.o -c "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/servidor.c"

CMakeFiles/Servidor.dir/servidor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Servidor.dir/servidor.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/servidor.c" > CMakeFiles/Servidor.dir/servidor.c.i

CMakeFiles/Servidor.dir/servidor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Servidor.dir/servidor.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/servidor.c" -o CMakeFiles/Servidor.dir/servidor.c.s

# Object files for target Servidor
Servidor_OBJECTS = \
"CMakeFiles/Servidor.dir/servidor.c.o"

# External object files for target Servidor
Servidor_EXTERNAL_OBJECTS =

Servidor.exe: CMakeFiles/Servidor.dir/servidor.c.o
Servidor.exe: CMakeFiles/Servidor.dir/build.make
Servidor.exe: CMakeFiles/Servidor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Servidor.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Servidor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Servidor.dir/build: Servidor.exe

.PHONY : CMakeFiles/Servidor.dir/build

CMakeFiles/Servidor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Servidor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Servidor.dir/clean

CMakeFiles/Servidor.dir/depend:
	cd "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/cmake-build-debug" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/cmake-build-debug" "/cygdrive/c/Users/pcdar/OneDrive/Documentos/GitHub/RC-PL-2021/Ficha 3/Resolucao/Ex2/Proj Aux/cmake-build-debug/CMakeFiles/Servidor.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Servidor.dir/depend
