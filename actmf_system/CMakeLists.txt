project (environment)

add_executable(${PROJECT_NAME} ../actmf_interface/abstract_service.cpp environment_actor.cpp environment.cpp)
target_link_libraries(${PROJECT_NAME} ${CAF_CORE_LIB} ${CAF_IO_LIB} dl)