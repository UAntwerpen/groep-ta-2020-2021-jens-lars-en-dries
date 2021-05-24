project(TO_GROEP)

set( Qt5Core_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Core")
set( Qt5Widgets_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Widgets")
set( Qt5Gui_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Gui")
set( Qt5Multimedia_DIR  "/home/lars/Qt5.12.10/5.12.10/gcc_64/lib/cmake/Qt5Multimedia")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(HEADER_FILES
        ../parser/EnvironmentParser.h
        ../parser/LAParser.h
        ../parser/AbstractParser.h
        trainagentwindow.ui
        trainagentwindow.h
        mainwindow.h
        world.h)

set(SOURCE_FILES
        ../parser/EnvironmentParser.cpp
        ../parser/LAParser.cpp
        ../parser/AbstractParser.cpp
        mainwindow.cpp
        world.cpp
        trainagentwindow.cpp)

# Optimizer compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_library(vis_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(vis_lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
qt5_use_modules(vis_lib Core Widgets Gui)
