cmake_minimum_required(VERSION 3.15)
project(TO_Groep)

set(CMAKE_CXX_STANDARD 17)
# Compiler flags for performance improvements and warnings
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

add_executable(TO_Groep main.cpp datastructures/Environment.cpp datastructures/Environment.h datastructures/LA.cpp datastructures/LA.h datastructures/State.cpp datastructures/State.h datastructures/Agent.cpp datastructures/Agent.h parser/AbstractParser.cpp parser/AbstractParser.h)

add_executable(TESTS tests/test.cpp datastructures/Environment.cpp datastructures/Environment.h datastructures/LA.cpp datastructures/LA.h datastructures/State.cpp datastructures/State.h datastructures/Agent.cpp datastructures/Agent.h tests/catch.hpp tests/catch.cpp random/Random.cpp random/Random.h parser/AbstractParser.cpp parser/AbstractParser.h parser/LAParser.cpp parser/LAParser.h)