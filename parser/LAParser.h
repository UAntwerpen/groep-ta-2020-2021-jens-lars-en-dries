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
    bool parseFile(LA* parsing_LA);

    void parseState(TiXmlElement* state_element,State* parsing_state);

    tuple<string, map<string, float>> parseAction(TiXmlElement* action_element);

    void parseEnvironment(TiXmlElement* environment_element, Environment* parsing_environment);
private:
    vector<int> fAllowed_actions;
    int width;
    int heigth;
    std::map<pair<int, int>, State*> coordsmap;
};


#endif //TO_GROEP_LAPARSER_H
