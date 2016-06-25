cmake_minimum_required(VERSION 2.6)

project (actmf_core)

add_library(${PROJECT_NAME} SHARED factory.cpp actor.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)