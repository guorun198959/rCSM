# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/shaoan/projects/rCSM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shaoan/projects/rCSM/build

# Include any dependencies generated for this target.
include CMakeFiles/testrcsm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testrcsm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testrcsm.dir/flags.make

CMakeFiles/testrcsm.dir/test.cpp.o: CMakeFiles/testrcsm.dir/flags.make
CMakeFiles/testrcsm.dir/test.cpp.o: ../test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/shaoan/projects/rCSM/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/testrcsm.dir/test.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/testrcsm.dir/test.cpp.o -c /home/shaoan/projects/rCSM/test.cpp

CMakeFiles/testrcsm.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testrcsm.dir/test.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/shaoan/projects/rCSM/test.cpp > CMakeFiles/testrcsm.dir/test.cpp.i

CMakeFiles/testrcsm.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testrcsm.dir/test.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/shaoan/projects/rCSM/test.cpp -o CMakeFiles/testrcsm.dir/test.cpp.s

CMakeFiles/testrcsm.dir/test.cpp.o.requires:
.PHONY : CMakeFiles/testrcsm.dir/test.cpp.o.requires

CMakeFiles/testrcsm.dir/test.cpp.o.provides: CMakeFiles/testrcsm.dir/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/testrcsm.dir/build.make CMakeFiles/testrcsm.dir/test.cpp.o.provides.build
.PHONY : CMakeFiles/testrcsm.dir/test.cpp.o.provides

CMakeFiles/testrcsm.dir/test.cpp.o.provides.build: CMakeFiles/testrcsm.dir/test.cpp.o

# Object files for target testrcsm
testrcsm_OBJECTS = \
"CMakeFiles/testrcsm.dir/test.cpp.o"

# External object files for target testrcsm
testrcsm_EXTERNAL_OBJECTS =

testrcsm: CMakeFiles/testrcsm.dir/test.cpp.o
testrcsm: CMakeFiles/testrcsm.dir/build.make
testrcsm: /opt/ros/indigo/lib/libpcl_ros_filters.so
testrcsm: /opt/ros/indigo/lib/libpcl_ros_io.so
testrcsm: /opt/ros/indigo/lib/libpcl_ros_tf.so
testrcsm: /usr/lib/libpcl_common.so
testrcsm: /usr/lib/libpcl_octree.so
testrcsm: /usr/lib/libpcl_io.so
testrcsm: /usr/lib/libpcl_kdtree.so
testrcsm: /usr/lib/libpcl_search.so
testrcsm: /usr/lib/libpcl_sample_consensus.so
testrcsm: /usr/lib/libpcl_filters.so
testrcsm: /usr/lib/libpcl_features.so
testrcsm: /usr/lib/libpcl_keypoints.so
testrcsm: /usr/lib/libpcl_segmentation.so
testrcsm: /usr/lib/libpcl_visualization.so
testrcsm: /usr/lib/libpcl_outofcore.so
testrcsm: /usr/lib/libpcl_registration.so
testrcsm: /usr/lib/libpcl_recognition.so
testrcsm: /usr/lib/libpcl_surface.so
testrcsm: /usr/lib/libpcl_people.so
testrcsm: /usr/lib/libpcl_tracking.so
testrcsm: /usr/lib/libpcl_apps.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
testrcsm: /usr/lib/x86_64-linux-gnu/libqhull.so
testrcsm: /usr/lib/libOpenNI.so
testrcsm: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
testrcsm: /usr/lib/libvtkCommon.so.5.8.0
testrcsm: /usr/lib/libvtkRendering.so.5.8.0
testrcsm: /usr/lib/libvtkHybrid.so.5.8.0
testrcsm: /usr/lib/libvtkCharts.so.5.8.0
testrcsm: /opt/ros/indigo/lib/libdynamic_reconfigure_config_init_mutex.so
testrcsm: /opt/ros/indigo/lib/libnodeletlib.so
testrcsm: /opt/ros/indigo/lib/libbondcpp.so
testrcsm: /usr/lib/x86_64-linux-gnu/libuuid.so
testrcsm: /opt/ros/indigo/lib/libclass_loader.so
testrcsm: /usr/lib/libPocoFoundation.so
testrcsm: /usr/lib/x86_64-linux-gnu/libdl.so
testrcsm: /opt/ros/indigo/lib/libroslib.so
testrcsm: /opt/ros/indigo/lib/librospack.so
testrcsm: /usr/lib/x86_64-linux-gnu/libpython2.7.so
testrcsm: /usr/lib/x86_64-linux-gnu/libtinyxml.so
testrcsm: /opt/ros/indigo/lib/librosbag.so
testrcsm: /opt/ros/indigo/lib/librosbag_storage.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
testrcsm: /opt/ros/indigo/lib/libroslz4.so
testrcsm: /usr/lib/x86_64-linux-gnu/liblz4.so
testrcsm: /opt/ros/indigo/lib/libtopic_tools.so
testrcsm: /opt/ros/indigo/lib/libtf.so
testrcsm: /opt/ros/indigo/lib/libtf2_ros.so
testrcsm: /opt/ros/indigo/lib/libactionlib.so
testrcsm: /opt/ros/indigo/lib/libmessage_filters.so
testrcsm: /opt/ros/indigo/lib/libroscpp.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_signals.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
testrcsm: /opt/ros/indigo/lib/libxmlrpcpp.so
testrcsm: /opt/ros/indigo/lib/libtf2.so
testrcsm: /opt/ros/indigo/lib/libroscpp_serialization.so
testrcsm: /opt/ros/indigo/lib/librosconsole.so
testrcsm: /opt/ros/indigo/lib/librosconsole_log4cxx.so
testrcsm: /opt/ros/indigo/lib/librosconsole_backend_interface.so
testrcsm: /usr/lib/liblog4cxx.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_regex.so
testrcsm: /opt/ros/indigo/lib/librostime.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
testrcsm: /opt/ros/indigo/lib/libcpp_common.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_system.so
testrcsm: /usr/lib/x86_64-linux-gnu/libboost_thread.so
testrcsm: /usr/lib/x86_64-linux-gnu/libpthread.so
testrcsm: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
testrcsm: CMakeFiles/testrcsm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable testrcsm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testrcsm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testrcsm.dir/build: testrcsm
.PHONY : CMakeFiles/testrcsm.dir/build

CMakeFiles/testrcsm.dir/requires: CMakeFiles/testrcsm.dir/test.cpp.o.requires
.PHONY : CMakeFiles/testrcsm.dir/requires

CMakeFiles/testrcsm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testrcsm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testrcsm.dir/clean

CMakeFiles/testrcsm.dir/depend:
	cd /home/shaoan/projects/rCSM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shaoan/projects/rCSM /home/shaoan/projects/rCSM /home/shaoan/projects/rCSM/build /home/shaoan/projects/rCSM/build /home/shaoan/projects/rCSM/build/CMakeFiles/testrcsm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testrcsm.dir/depend

