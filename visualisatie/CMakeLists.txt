project(TO_GROEP)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set( Qt5Core_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Core")
set( Qt5Widgets_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Widgets")
set( Qt5Gui_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Gui")
set( Qt5Multimedia_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Multimedia")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(HEADER_FILES
        mainwindow.h
        world.h)

set(SOURCE_FILES
        mainwindow.cpp
        world.cpp)

add_library(vis_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
qt5_use_modules(vis_lib Core Widgets Gui)
