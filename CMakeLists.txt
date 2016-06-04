project(actmf)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CAF_LIBRARIES caf_core)

add_executable(actmf src/main.cpp)
target_link_libraries(actmf ${CAF_LIBRARIES})

install(TARGETS actmf RUNTIME DESTINATION bin)
