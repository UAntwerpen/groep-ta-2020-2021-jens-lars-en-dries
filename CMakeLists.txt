cmake_minimum_required(VERSION 3.15)

project(TO_Groep)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set( Qt5Core_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Core")
set( Qt5Widgets_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Widgets")
set( Qt5Gui_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Gui")
set( Qt5Multimedia_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Multimedia")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(CMAKE_CXX_STANDARD 17)
# Compiler flags for performance improvements and warnings
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.cpp datastructures/Environment.cpp datastructures/Environment.h algorithms/QLearning.h algorithms/QLearning.cpp datastructures/LA.cpp datastructures/LA.h
        datastructures/State.cpp datastructures/State.h algorithms/MCLearning.cpp algorithms/MCLearning.h random/Random.cpp random/Random.h
        datastructures/MDPState.cpp datastructures/MDPState.h algorithms/QLearning.cpp algorithms/QLearning.h
        visualisatie/trainagentwindow.cpp visualisatie/trainagentwindow.h visualisatie/trainagentwindow.ui
        visualisatie/mainwindow.h visualisatie/world.h visualisatie/mainwindow.cpp visualisatie/world.cpp visualisatie/ui_newwindow.h visualisatie/newwindow.h visualisatie/newwindow.cpp)

add_executable(TO_Groep ${SOURCE_FILES})
qt5_use_modules(TO_Groep Core Widgets Gui)

target_link_libraries(TO_Groep parser_lib procedural_generation_lib )

add_executable(TESTS tests/test.cpp datastructures/Environment.cpp datastructures/Environment.h algorithms/QLearning.h algorithms/QLearning.cpp datastructures/LA.cpp
        datastructures/LA.h datastructures/State.cpp datastructures/State.h algorithms/MCLearning.cpp algorithms/MCLearning.h tests/catch.hpp random/Random.cpp random/Random.h
        tests/catch.cpp datastructures/MDPState.cpp datastructures/MDPState.h )

target_link_libraries(TESTS parser_lib procedural_generation_lib)

add_subdirectory(parser)
add_subdirectory(procederual-generation)