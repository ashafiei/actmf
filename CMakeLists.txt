cmake_minimum_required(VERSION 2.6)

project(actmf)

set (CMAKE_CXX_STANDARD 11)

find_library (CAF_CORE_LIB NAMES caf_core PATH /usr/lib)
find_library (CAF_IO_LIB NAMES caf_io PATH /usr/lib)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

include_directories(".")

add_subdirectory(actmf_actor)
add_subdirectory(actmf_system)
add_subdirectory(actmf_application)