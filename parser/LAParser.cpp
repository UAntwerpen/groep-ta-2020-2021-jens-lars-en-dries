#include "LAParser.h"

bool LAParser::parseFile(string inputFile, LA *parsing_LA) {
    return false;
}

void LAParser::parseState(TiXmlElement *state_element, State *parsing_state) {

}

tuple<string, map<string, float>> LAParser::parseAction(TiXmlElement *action_element) {
    return tuple<string, map<string, float>>();
}

void LAParser::parseEnvironment(TiXmlElement *environment_element, Environment *parsing_environment) {

}
