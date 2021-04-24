#ifndef TO_GROEP_ABSTRACTPARSER_H
#define TO_GROEP_ABSTRACTPARSER_H

#include "tinyxml/tinyxml.h"
#include <string>

using std::string;

class AbstractParser {
public:
    AbstractParser() = default;

    ~AbstractParser() = default;

    void loadFile(string filename);

    TiXmlElement* getRoot();
private:
    TiXmlElement* fRoot = nullptr;
    TiXmlDocument fDoc;
};


#endif //TO_GROEP_ABSTRACTPARSER_H
