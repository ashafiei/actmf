cmake_minimum_required(VERSION 2.6)

project (examples)

set(ACTMF_CORE_LIB actmf_core)
set(ENVIRONMENT environment)
set(APPLICATION application)

add_executable(${ENVIRONMENT} environment.cpp)
target_link_libraries(${ENVIRONMENT} ${ACTMF_CORE_LIB})

add_executable(${APPLICATION} application.cpp)
target_link_libraries(${APPLICATION} ${ACTMF_CORE_LIB})