cmake_minimum_required(VERSION 2.6)

project (actmf_actor)

find_library (CAF_CORE_LIB NAMES caf_core)
find_library (CAF_IO_LIB NAMES caf_io)
set(ACTMF_CORE_LIB actmf_core)

file(GLOB ACTORS *.h)

foreach(file ${ACTORS})
  get_filename_component(file_name ${file} NAME_WE)
  add_library(${file_name} SHARED ../libactmf_core/abstract_actor.cpp ${file})
  set_target_properties(${file_name} PROPERTIES LINKER_LANGUAGE CXX)
  target_link_libraries(${file_name} ${ACTMF_CORE_LIB} ${CAF_CORE_LIB} ${CAF_IO_LIB})
  install(TARGETS ${file_name} DESTINATION lib)
endforeach()