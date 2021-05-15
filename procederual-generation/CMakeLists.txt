cmake_minimum_required(VERSION 3.17)
project(Procedural_Generator)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES RiverBezier.h LavaPools.h)

set(SOURCE_FILES RiverBezier.cpp LavaPools.cpp)

# Optimizer compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

add_library(procedural_generation_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})