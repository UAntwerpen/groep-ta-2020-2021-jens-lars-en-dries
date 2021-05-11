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
    /*
     * Function handles the parsing of a Learning Automaton. All the data gets added to the LA object provided by user.
     * @param parsing_LA Pointer to new object of type LA, all data gets written to this object.
     * @return bool True if the parsing finishes correctly.
     */
    bool parseFile(LA* parsing_LA);

    /*
     * Helper function of parseFile(LA* parsing_LA), that parses individual states of the LA.
     * @param state_element Pointer to object of type TiXmlElement which contains the data of the state.
     * @param parsing_state Pointer to object of type State, data
     */
    void parseState(TiXmlElement* state_element,State* parsing_state);

private:
    vector<int> fAllowed_actions;
    int fWidth;
    int fHeight;
    std::map<pair<int, int>, State*> fCoordsmap;
};


#endif //TO_GROEP_LAPARSER_H
