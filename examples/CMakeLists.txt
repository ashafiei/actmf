cmake_minimum_required(VERSION 2.6)

project (examples)

set(ACTMF_CORE_LIBRARY actmf_core)
set(ENVIRONMENT_ACTOR_EXAMPLE factory_actor)
set(USER_ADDITION_ACTOR_EXAMPLE user_actor)

add_executable(${ENVIRONMENT_ACTOR_EXAMPLE} environment.cpp)
target_link_libraries(${ENVIRONMENT_ACTOR_EXAMPLE} ${ACTMF_CORE_LIBRARY})

add_executable(${USER_ADDITION_ACTOR_EXAMPLE} user_addition.cpp)
target_link_libraries(${USER_ADDITION_ACTOR_EXAMPLE} ${ACTMF_CORE_LIBRARY})