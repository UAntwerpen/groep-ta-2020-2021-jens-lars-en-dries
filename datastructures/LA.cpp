//
// Created by driesdemaeseneer on 4/15/21.
//

#include <tuple>
#include <random>
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
}

/*LA::~LA() {
    for (int i = 0; i<all_states.size();i++) {
        delete all_states[all_states.size()-1-i];
    }
}*/

LA::LA() {
    width = 0;
    height = 0;
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
