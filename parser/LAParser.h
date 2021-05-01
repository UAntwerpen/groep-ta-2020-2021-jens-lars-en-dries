#ifndef TO_GROEP_LAPARSER_H
#define TO_GROEP_LAPARSER_H


#include "AbstractParser.h"
#include "tinyxml/tinyxml.h"
#include "../datastructures/LA.h"

class LAParser : public AbstractParser {
public:
    bool parseFile(string inputFile, LA* parsing_LA);
private:

};


#endif //TO_GROEP_LAPARSER_H
