# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mattia/CLionProjects/Stealth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mattia/CLionProjects/Stealth/build

# Utility rule file for pack-data.

# Include the progress variables for this target.
include CMakeFiles/pack-data.dir/progress.make

CMakeFiles/pack-data: stealth.dat


stealth.dat: ../res/cursors.png
stealth.dat: ../res/fonts
stealth.dat: ../res/map.png
stealth.dat: ../res/map_ascii.png
stealth.dat: ../res/maps
stealth.dat: ../res/music
stealth.dat: ../res/splashscreen.png
stealth.dat: ../res/unifi.png
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/mattia/CLionProjects/Stealth/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Zipping to /home/mattia/CLionProjects/Stealth/build/stealth.dat"
	cd /home/mattia/CLionProjects/Stealth/res && /usr/bin/cmake -E tar cf /home/mattia/CLionProjects/Stealth/build/stealth.dat --format=zip -- /home/mattia/CLionProjects/Stealth/res/cursors.png /home/mattia/CLionProjects/Stealth/res/fonts /home/mattia/CLionProjects/Stealth/res/map.png /home/mattia/CLionProjects/Stealth/res/map_ascii.png /home/mattia/CLionProjects/Stealth/res/maps /home/mattia/CLionProjects/Stealth/res/music /home/mattia/CLionProjects/Stealth/res/splashscreen.png /home/mattia/CLionProjects/Stealth/res/unifi.png

pack-data: CMakeFiles/pack-data
pack-data: stealth.dat
pack-data: CMakeFiles/pack-data.dir/build.make

.PHONY : pack-data

# Rule to build all files generated by this target.
CMakeFiles/pack-data.dir/build: pack-data

.PHONY : CMakeFiles/pack-data.dir/build

CMakeFiles/pack-data.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pack-data.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pack-data.dir/clean

CMakeFiles/pack-data.dir/depend:
	cd /home/mattia/CLionProjects/Stealth/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mattia/CLionProjects/Stealth /home/mattia/CLionProjects/Stealth /home/mattia/CLionProjects/Stealth/build /home/mattia/CLionProjects/Stealth/build /home/mattia/CLionProjects/Stealth/build/CMakeFiles/pack-data.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pack-data.dir/depend

