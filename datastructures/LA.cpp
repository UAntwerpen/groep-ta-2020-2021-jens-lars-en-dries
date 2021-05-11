#include <tuple>
#include <random>
#include <sstream>
#include "LA.h"
#include "../parser/tinyxml/tinyxml.h"

void LA::reset() {

}

State *LA::G(State *in_state, int in_action) {
    // action (int), 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
    switch (in_action) {
        case(0):{
            if(in_state->getCoordinates().first==height) return in_state;
            else{
                return coordinates_to_state[std::make_pair(in_state->getCoordinates().first, in_state->getCoordinates().second+1)];
            }
        }
        case(1):{
            if(in_state->getCoordinates().first==width) return in_state;
            else{
                return coordinates_to_state[std::make_pair(in_state->getCoordinates().first+1, in_state->getCoordinates().second)];
            }
        }
        case(2):{
            if(in_state->getCoordinates().first==0) return in_state;
            else{
                return coordinates_to_state[std::make_pair(in_state->getCoordinates().first, in_state->getCoordinates().second-1)];
            }
        }
        case(3):{
            if(in_state->getCoordinates().first==0) return in_state;
            else{
                return coordinates_to_state[std::make_pair(in_state->getCoordinates().first-1, in_state->getCoordinates().second)];
            }
        }
        default:{
            break;
        }
    }
    return nullptr;
}

int LA::pickAction(State *in_state) {

    // get distributions according to environment dynamics (current state and action chosen by agent)
    std::vector<int> state_rewards;
    std::vector<float> probabilities;

    for (auto const &distribution: in_state->getProbabilities()) {
        state_rewards.push_back(distribution.first);
        probabilities.push_back(distribution.second);
    }
    // sampling according to distributions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d(probabilities.begin(), probabilities.end());

    return state_rewards[d(gen)];
}

State *LA::coordinatesToState(std::tuple<int, int> in_coords) {
    return coordinates_to_state[std::make_pair(std::get<0>(in_coords), std::get<1>(in_coords))];
}

std::vector<State *> LA::getAllStates() {
    return all_states;
}

std::vector<int> LA::getAllActions() {
    return all_actions;
}

LA::LA(const int height, const int width, std::pair<int, int> start_coordinates, std::vector<int> &actions) {
    properly_init = this;
    this->height = height;
    this->width = width;
    for(int i = 0; i < width; i++){
        for (int j = 0; j < height; j++) {
            all_states.emplace_back(new State(i, j, actions));
            if(std::make_pair(i, j)==start_coordinates) start_state = all_states[all_states.size()-1];
            coordinates_to_state[std::make_pair(i, j)] = all_states[all_states.size()-1];
        }
    }
    all_actions = actions;
}

/*LA::~LA() {
    for (int i = 0; i<all_states.size();i++) {
        delete all_states[all_states.size()-1-i];
    }
}*/

LA::LA() {
    width = 0;
    height = 0;
    properly_init = this;
}

bool LA::isProperlyInitialized() {
    return properly_init==this;
}

int LA::argmax(State *in_state) {
    int action;
    float max_value = -1 * std::numeric_limits<float>::min();
    for(auto& it: in_state->getQValue()){
        if(it.second>max_value){
            max_value = it.second;
            action = it.first;
        }
    }
    return action;
}

void LA::resetCounter() {
    for(auto& it:all_states) it->resetCounter();
}

bool LA::addState(State *newState) {
    all_states.push_back(newState);
    return true;
}

bool LA::save(std::string outputFileName) {
    TiXmlDocument doc;
    TiXmlElement* root = new TiXmlElement( "LA" );
    doc.LinkEndChild(root);

    TiXmlElement* defstates = new TiXmlElement( "DEFSTATES" );
    root->LinkEndChild(defstates);

    TiXmlElement* posactions = new TiXmlElement( "POSACTIONS" );
    root->LinkEndChild(posactions);
    for(unsigned int j = 0; j < getAllActions().size(); j++){
        std::stringstream s;
        s << getAllActions()[j];
        TiXmlElement* posaction = new TiXmlElement( "posaction" );
        posactions->LinkEndChild(posaction);
        TiXmlText* action_txt = new TiXmlText(s.str().c_str());
        posaction->LinkEndChild(action_txt);
    }

    TiXmlElement* states = new TiXmlElement( "STATES" );
    root->LinkEndChild(states);

    TiXmlElement* startstate = new TiXmlElement( "startstate" );
    root->LinkEndChild(startstate);

    for(unsigned int i = 0; i < all_states.size(); i++){
        TiXmlElement* state = new TiXmlElement( "STATE" );
        states->LinkEndChild(state);
        TiXmlElement* defstate = new TiXmlElement( "defstate" );
        defstates->LinkEndChild(defstate);
        std::stringstream ss_name;
        ss_name << "state_" << i;
        TiXmlText* name1 = new TiXmlText( (ss_name.str()).c_str() );
        TiXmlText* name2 = new TiXmlText( (ss_name.str()).c_str() );
        defstate->LinkEndChild(name1);
        TiXmlElement* el_name = new TiXmlElement( "name" );
        state->LinkEndChild(el_name);
        el_name->LinkEndChild(name2);
        if(all_states[i] == start_state){
            TiXmlText* startstate_txt = new TiXmlText(ss_name.str().c_str());
            startstate->LinkEndChild(startstate_txt);
        }

        TiXmlElement* x_coord = new TiXmlElement( "x_coord" );
        state->LinkEndChild(x_coord);
        ss_name.str("");
        ss_name << getAllStates()[i]->getCoordinates().first;
        TiXmlText* x_text = new TiXmlText( (ss_name.str()).c_str() );
        x_coord->LinkEndChild(x_text);
        TiXmlElement* y_coord = new TiXmlElement( "y_coord" );
        state->LinkEndChild(y_coord);
        ss_name.str("");
        ss_name << getAllStates()[i]->getCoordinates().second;
        TiXmlText* y_text = new TiXmlText( (ss_name.str()).c_str() );
        y_coord->LinkEndChild(y_text);

        TiXmlElement* actions = new TiXmlElement( "ACTIONS" );
        state->LinkEndChild(actions);

        //Loops over all the actions of the state.
        for(unsigned int j = 0; j < getAllActions().size(); j++){
            TiXmlElement* action = new TiXmlElement( "ACTION" );
            actions->LinkEndChild(action);
            // a_Value gets saved
            std::stringstream s;
            s << getAllActions()[j];

            TiXmlElement* a_value = new TiXmlElement( "a_value" );
            action->LinkEndChild(a_value);
            TiXmlText* action_txt = new TiXmlText(s.str().c_str());
            a_value->LinkEndChild(action_txt);
            // Q_Value gets saved
            s.str("");
            TiXmlElement* q_value = new TiXmlElement( "q_value" );
            action->LinkEndChild(q_value);
            s << (float)all_states[i]->getValue(getAllActions()[j]);
            TiXmlText* q_txt = new TiXmlText(s.str().c_str());
            q_value->LinkEndChild(q_txt);
            // Probability gets saved
            s.str("");
            TiXmlElement* probability = new TiXmlElement( "probability" );
            action->LinkEndChild(probability);
            s << (float)all_states[i]->getProbabilities()[getAllActions()[j]];
            TiXmlText* probability_txt = new TiXmlText(s.str().c_str());
            probability->LinkEndChild(probability_txt);
        }



    }


    doc.SaveFile(("data/" + outputFileName).c_str());
    return true;
}
