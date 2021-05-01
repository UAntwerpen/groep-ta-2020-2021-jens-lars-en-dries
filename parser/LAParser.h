#ifndef TO_GROEP_LAPARSER_H
#define TO_GROEP_LAPARSER_H


#include "AbstractParser.h"
#include "tinyxml/tinyxml.h"
#include "../datastructures/LA.h"
#include "../datastructures/Environment.h"

#include <map>
#include <tuple>
#include <string>

using namespace std;

class LAParser : public AbstractParser {
public:
    bool parseFile(string inputFile, LA* parsing_LA);

    void parseState(TiXmlElement* state_element,State* parsing_state);

    tuple<string, map<string, float>> parseAction(TiXmlElement* action_element);

    void parseEnvironment(TiXmlElement* environment_element, Environment* parsing_environment);
private:

};


#endif //TO_GROEP_LAPARSER_H
