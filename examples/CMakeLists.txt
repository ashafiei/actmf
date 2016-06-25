cmake_minimum_required(VERSION 2.6)

project (examples)

set(ACTMF_CORE_LIBRARY actmf_core)
set(FACTORY_ACTOR_EXAMPLE factory_actor)
set(USER_ACTOR_EXAMPLE user_actor)

add_executable(${FACTORY_ACTOR_EXAMPLE} factory_actor.cpp)
target_link_libraries(${FACTORY_ACTOR_EXAMPLE} ${ACTMF_CORE_LIBRARY})

add_executable(${USER_ACTOR_EXAMPLE} user_actor.cpp)
target_link_libraries(${USER_ACTOR_EXAMPLE} ${ACTMF_CORE_LIBRARY})