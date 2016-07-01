cmake_minimum_required(VERSION 2.6)

project (actmf_core)

find_library (CAF_CORE_LIB NAMES caf_core)
find_library (CAF_IO_LIB NAMES caf_io)


add_library(${PROJECT_NAME} SHARED ${file})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${CAF_CORE_LIB} ${CAF_IO_LIB})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
