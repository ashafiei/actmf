cmake_minimum_required(VERSION 2.6)

project (actmf_core)

find_library (CAF_CORE_LIBRARY NAMES caf_core)
find_library (CAF_IO_LIBRARY NAMES caf_io)

file(GLOB_RECURSE LIB_ACTMF_HDRS "actmf/*.cpp")
file(GLOB_RECURSE LIB_ACTMF_SRC "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${LIB_ACTMF_HDRS} ${LIB_ACTMF_SRC})
target_link_libraries(${PROJECT_NAME} ${CAF_CORE_LIBRARY} ${CAF_IO_LIBRARY})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)