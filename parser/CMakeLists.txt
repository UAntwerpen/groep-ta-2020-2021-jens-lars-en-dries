project(TO_GROEP)

set(HEADER_FILES
        AbstractParser.h
        LAParser.h
        tinyxml/tinyxml.h
        tinyxml/tinystr.h
        )

set(SOURCE_FILES
        AbstractParser.cpp
        LAParser.cpp
        tinyxml/tinystr.cpp
        tinyxml/tinyxml.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        EnvironmentParser.cpp EnvironmentParser.h)

# Optimizer compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

add_library(parser_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})