# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /opt/clion-2021.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2021.2.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/sami_lang_compiler_c___version.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/sami_lang_compiler_c___version.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sami_lang_compiler_c___version.dir/flags.make

CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.o: CMakeFiles/sami_lang_compiler_c___version.dir/flags.make
CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.o -c "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/main.cpp"

CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/main.cpp" > CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.i

CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/main.cpp" -o CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.s

CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.o: CMakeFiles/sami_lang_compiler_c___version.dir/flags.make
CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.o: ../src/lexer/lib/token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.o -c "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/src/lexer/lib/token.cpp"

CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/src/lexer/lib/token.cpp" > CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.i

CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/src/lexer/lib/token.cpp" -o CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.s

CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.o: CMakeFiles/sami_lang_compiler_c___version.dir/flags.make
CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.o: ../src/lexer/lib/lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.o -c "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/src/lexer/lib/lexer.cpp"

CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/src/lexer/lib/lexer.cpp" > CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.i

CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/src/lexer/lib/lexer.cpp" -o CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.s

# Object files for target sami_lang_compiler_c___version
sami_lang_compiler_c___version_OBJECTS = \
"CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.o" \
"CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.o" \
"CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.o"

# External object files for target sami_lang_compiler_c___version
sami_lang_compiler_c___version_EXTERNAL_OBJECTS =

sami_lang_compiler_c___version: CMakeFiles/sami_lang_compiler_c___version.dir/main.cpp.o
sami_lang_compiler_c___version: CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/token.cpp.o
sami_lang_compiler_c___version: CMakeFiles/sami_lang_compiler_c___version.dir/src/lexer/lib/lexer.cpp.o
sami_lang_compiler_c___version: CMakeFiles/sami_lang_compiler_c___version.dir/build.make
sami_lang_compiler_c___version: CMakeFiles/sami_lang_compiler_c___version.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable sami_lang_compiler_c___version"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sami_lang_compiler_c___version.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sami_lang_compiler_c___version.dir/build: sami_lang_compiler_c___version
.PHONY : CMakeFiles/sami_lang_compiler_c___version.dir/build

CMakeFiles/sami_lang_compiler_c___version.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sami_lang_compiler_c___version.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sami_lang_compiler_c___version.dir/clean

CMakeFiles/sami_lang_compiler_c___version.dir/depend:
	cd "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version" "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version" "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug" "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug" "/media/sami/Dev Space/sami-lang/sami-lang-compiler-c++-version/cmake-build-debug/CMakeFiles/sami_lang_compiler_c___version.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/sami_lang_compiler_c___version.dir/depend

