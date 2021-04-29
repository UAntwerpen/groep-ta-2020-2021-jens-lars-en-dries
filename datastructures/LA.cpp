//
// Created by driesdemaeseneer on 4/15/21.
//

#include <tuple>
#include "LA.h"

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
                return coordinates_to_state[std::make_pair(in_state->getCoordinates().first-1, in_state->getCoordinates().second+1)];
            }
        }
        default:{
            break;
        }
    }
    return nullptr;
}

int LA::pickAction(State *in_state) {
    float current_max = std::numeric_limits<float>::min();
    int current_action;
    for(auto it: in_state->getQValue()){
        if(it.second>current_max){
            current_action = it.first;
            current_max = it.second;
        }
    }
    return current_action;
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
    this->height = height;
    this->width = width;
    for(int i = 0; i < width; i++){
        for (int j = 0; j < height; j++) {
            all_states.emplace_back(new State(i, j, actions));
            if(std::make_pair(i, j)==start_coordinates) start_state = all_states[all_states.size()-1];
            coordinates_to_state[std::make_pair(i, j)] = all_states[all_states.size()-1];
        }
    }
}

LA::~LA() {
    for (int i = 0; i<all_states.size();i++) {
        delete all_states[all_states.size()-1-i];
    }
}
