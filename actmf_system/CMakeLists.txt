project (environment)

file(GLOB ENV_SRC *.cpp)

add_executable(${PROJECT_NAME} ../actmf_interface/abstract_service.cpp ${ENV_SRC})
target_link_libraries(${PROJECT_NAME} ${CAF_LIB} ${OPENCV_LIB} dl)