cmake_minimum_required(VERSION 2.6)

project (actmf_core)

file(GLOB_RECURSE LIB_ACTMF_HDRS "actmf/*.cpp")
file(GLOB_RECURSE LIB_ACTMF_SRC "src/*.cpp")


add_library(${PROJECT_NAME} SHARED ${LIB_ACTMF_HDRS} ${LIB_ACTMF_SRC})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)