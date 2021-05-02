#include "LAParser.h"

bool LAParser::parseFile(LA *parsing_LA) {
    bool error = true;
    map<string, State*> hold_states;
    for (TiXmlElement *element = getRoot()->FirstChildElement() ; element != NULL ; element = element->NextSiblingElement()) {
        if (element->Value() == string("DEFSTATES")) {
            for(TiXmlElement *child = element->FirstChildElement() ; child != NULL ; child = child->NextSiblingElement()){
                if(child->Value() == string("defstate")){
                    State* new_state = new State();
                    hold_states[child->FirstChild()->ToText()->Value()] = new_state;
                }
            }
            error = false;
        }
    }
    if(error){
        cout << "No DEFSTATES segment in inputfile to parse.";
    }
    error = true;
    for (TiXmlElement *element = getRoot()->FirstChildElement() ; element != NULL ; element = element->NextSiblingElement()) {
        if (element->Value() == string("STATES")) {
            TiXmlElement * states_to_parse = element;
            error = false;
            }
        }
    if(error){
        cout << "No STATES segment in inputfile to parse.";
    }
    error = true;
    for (TiXmlElement *element = getRoot()->FirstChildElement() ; element != NULL ; element = element->NextSiblingElement()) {
        if (element->Value() == string("STATES")) {
            TiXmlElement * states_to_parse = element;
            error = false;
        }
    }
    if(error){
        cout << "No STATES segment in inputfile to parse.";
    }
    return true;
}

void LAParser::parseState(TiXmlElement *state_element, State *parsing_state) {

}

tuple<string, map<string, float>> LAParser::parseAction(TiXmlElement *action_element) {
    return tuple<string, map<string, float>>();
}

void LAParser::parseEnvironment(TiXmlElement *environment_element, Environment *parsing_environment) {

}
