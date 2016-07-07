project (application)

add_executable(${PROJECT_NAME} application.cpp)
target_link_libraries(${PROJECT_NAME} ${CAF_CORE_LIB} ${CAF_IO_LIB})