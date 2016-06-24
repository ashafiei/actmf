cmake_minimum_required(VERSION 2.6)
project(actmf)

add_executable(actmf main.cpp)

install(TARGETS actmf RUNTIME DESTINATION bin)
