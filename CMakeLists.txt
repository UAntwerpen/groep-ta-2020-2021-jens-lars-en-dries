cmake_minimum_required(VERSION 3.15)
project(TO_Groep)

set(CMAKE_CXX_STANDARD 17)
# Compiler flags for performance improvements and warnings
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

set(SOURCE_FILES main.cpp datastructures/Environment.cpp datastructures/Environment.h datastructures/LA.cpp datastructures/LA.h
        datastructures/State.cpp datastructures/State.h datastructures/Agent.cpp datastructures/Agent.h random/Random.cpp random/Random.h
        datastructures/MDPState.cpp datastructures/MDPState.h)
add_executable(TO_Groep ${SOURCE_FILES})

target_link_libraries(TO_Groep parser_lib)

add_executable(TESTS tests/test.cpp datastructures/Environment.cpp datastructures/Environment.h datastructures/LA.cpp
        datastructures/LA.h datastructures/State.cpp datastructures/State.h datastructures/Agent.cpp datastructures/Agent.h tests/catch.hpp
        tests/catch.cpp random/Random.cpp random/Random.h datastructures/MDPState.cpp datastructures/MDPState.h)

target_link_libraries(TESTS parser_lib)

add_subdirectory(parser)
