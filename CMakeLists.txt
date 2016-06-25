cmake_minimum_required(VERSION 2.6)

project(actmf)

set (CMAKE_CXX_STANDARD 11)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

add_subdirectory(libactmf_core)
add_subdirectory(examples)