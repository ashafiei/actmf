project (actmf_actor)

file(GLOB ACTORS *.cpp)

foreach(file ${ACTORS})
  get_filename_component(actor ${file} NAME_WE)
  add_library(${actor} SHARED ../actmf_interface/abstract_service.cpp ${actor}.cpp)
  target_link_libraries(${actor} ${CAF_CORE_LIB} ${CAF_IO_LIB})
  install(TARGETS ${actor} DESTINATION lib)
endforeach()
