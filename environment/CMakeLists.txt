cmake_minimum_required(VERSION 2.6)

project (environment)

find_library (CAF_CORE_LIB NAMES caf_core)
find_library (CAF_IO_LIB NAMES caf_io)
set(ACTMF_CORE_LIB actmf_core)

add_executable(${PROJECT_NAME} ../libactmf_core/abstract_actor.cpp environment_actor.cpp environment.cpp)
target_link_libraries(${PROJECT_NAME} ${ACTMF_CORE_LIB} ${CAF_CORE_LIB} ${CAF_IO_LIB} dl)