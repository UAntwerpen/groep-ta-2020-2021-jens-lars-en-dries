cmake_minimum_required(VERSION 3.17)
project(TO_Groep)

set(CMAKE_CXX_STANDARD 14)
# Compiler flags for performance improvements and warnings
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

add_executable(TO_Groep main.cpp Datastructures/MDP.cpp Datastructures/MDP.h Datastructures/LA.cpp Datastructures/LA.h Datastructures/State.cpp Datastructures/State.h Datastructures/Agent.cpp Datastructures/Agent.h)