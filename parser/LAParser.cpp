#include "LAParser.h"

bool LAParser::parseFile(LA *parsing_LA) {
    bool error = true;
    // Creates the required state objects.
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
    // Find the STATES segment in xml-file and put a pointer to the element in states_to_parse_element.
    TiXmlElement * states_to_parse_element;
    for (TiXmlElement *element = getRoot()->FirstChildElement() ; element != NULL ; element = element->NextSiblingElement()) {
        if (element->Value() == string("STATES")) {
            states_to_parse_element = element;
            error = false;
            }
        }
    if(error){
        cout << "No STATES segment in inputfile to parse.";
    }
    error = true;
    // Create vector of pointers to xml-elements containing the individual states.
    vector<TiXmlElement*> states_to_parse;
    for (TiXmlElement *element = states_to_parse_element->FirstChildElement() ; element != NULL ; element = element->NextSiblingElement()) {
        if (element->Value() == string("STATE")) {
            states_to_parse.push_back(element);
            error = false;
        }
    }
    if(error){
        cout << "No STATE segment in STATES.";
    }
    // Parses the POSACTIONS segment, this contains all the possible actions of the LA.
    for (TiXmlElement *element = getRoot()->FirstChildElement() ; element != NULL ; element = element->NextSiblingElement()) {
        if (element->Value() == string("POSACTIONS")) {
            for(TiXmlElement *child = element->FirstChildElement() ; child != NULL ; child = child->NextSiblingElement()){
                if(child->Value() == string("posaction")){
                    fAllowed_actions.push_back(stoi(child->FirstChild()->ToText()->Value()));
                }
            }
            error = false;
        }
    }
    if(error){
        cout << "No POSACTIONS segment in inputfile to parse.";
    }
//    if(states_to_parse.size() == 0) _assert ("No states found in STATES segment.", __FILE__, __LINE__);
    // Parse every state.
    for(unsigned int i = 0; i < states_to_parse.size(); i++){
        string name = states_to_parse[i]->FirstChildElement("name")->FirstChild()->ToText()->Value();
        parseState(states_to_parse[i], hold_states[name]);
    }
    // Add the states to the LA.
    for(auto state : hold_states){
        parsing_LA->addState(state.second);
    }
    // Add the additional required data to the LA.
    parsing_LA->setStartState(hold_states[getRoot()->FirstChildElement("startstate")->FirstChild()->ToText()->Value()]);
    parsing_LA->setAllActions(fAllowed_actions);
    parsing_LA->setHeight(fHeight);
    parsing_LA->setWidth(fWidth);
    parsing_LA->setCoordMap(fCoordsmap);
    return true;
}

void LAParser::parseState(TiXmlElement *state_element, State *parsing_state) {
    parsing_state->setActions(fAllowed_actions);
    // Run through the ACTIONS segment and add all the action's to the state.
    for (TiXmlElement *elem = state_element->FirstChildElement("ACTIONS");
         elem != NULL; elem = elem->NextSiblingElement()) {
        for (TiXmlElement *action = elem->FirstChildElement(); action != NULL; action = action->NextSiblingElement()) {
            parsing_state->setValue(stoi(action->FirstChildElement("a_value")->FirstChild()->ToText()->Value()),
                                    stof(action->FirstChildElement("q_value")->FirstChild()->ToText()->Value()));
            parsing_state->setProbability(stoi(action->FirstChildElement("a_value")->FirstChild()->ToText()->Value()),
                                    stof(action->FirstChildElement("probability")->FirstChild()->ToText()->Value()));
        }
    }
    // Add the x, y coordinates. After adding checks if the coords were larger than the largest recorded one.
    // If so then fWidth or fHeight get updated respectively.
    parsing_state->setX(stoi(state_element->FirstChildElement("x_coord")->FirstChild()->ToText()->Value()));
    if (stoi(state_element->FirstChildElement("x_coord")->FirstChild()->ToText()->Value()) + 1 > fWidth)
        fWidth = stoi(state_element->FirstChildElement("x_coord")->FirstChild()->ToText()->Value()) + 1;
    parsing_state->setY(stoi(state_element->FirstChildElement("y_coord")->FirstChild()->ToText()->Value()));
    if (stoi(state_element->FirstChildElement("y_coord")->FirstChild()->ToText()->Value()) + 1 > fHeight)
        fHeight = stoi(state_element->FirstChildElement("y_coord")->FirstChild()->ToText()->Value()) + 1;
    // Update the coordsmap.
    fCoordsmap[parsing_state->getCoordinates()] = parsing_state;
}
