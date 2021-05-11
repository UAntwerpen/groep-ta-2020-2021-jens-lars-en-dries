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

add_library(parser_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})