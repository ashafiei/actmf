cmake_minimum_required(VERSION 2.6)

project(actmf)

set (CMAKE_CXX_STANDARD 11)

set (CAF_LIB caf_core caf_io)
set (OPENCV_LIB opencv_core opencv_highgui opencv_ml opencv_imgproc)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

include_directories(".")

add_subdirectory(actmf_actor)
add_subdirectory(actmf_system)
add_subdirectory(actmf_application)