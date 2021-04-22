//
// Created by driesdemaeseneer on 4/15/21.
//

#include "State.h"

State *State::operator[](int action) const {
    for(auto it:action_to_state){
        if(it.first == action){
            return it.second;
        }
    }
    return nullptr;
}

float State::operator[](State *state) const {
    for(auto& it:state_to_probability){
        if(&it.first == &state){
            return it.second;
        }
    }
    return 0;
}

void State::setValue(int action, float in_value) {
    findActionValuePair(action).second = in_value;
}

std::pair<int, float > &State::findActionValuePair(int action) {
    for(auto& it: Q_value){
        if(it.first == action){
            return it;
        }
    }
}

float State::getValue(int action){
    for(auto& it: Q_value){
        if(it.first == action){
            return it.second;
        }
    }
}

float State::pToState(State *in_state) {
    for(auto it:state_to_probability){
        if(it.first == in_state) return it.second;
    }
    return 0;
}

const std::vector<int> &State::getActions() const {
    return actions;
}

void State::setActions(const std::vector<int> &actions) {
    State::actions = actions;
}

const std::vector<std::pair<int, float >> &State::getQValue() const {
    return Q_value;
}

void State::setValue1(const std::vector<std::pair<int, float >> &value) {
    State::Q_value = value;
}

const std::vector<std::pair<int, State *>> &State::getActionToState() const {
    return action_to_state;
}

void State::setActionToState(const std::vector<std::pair<int, State *>> &actionToState) {
    action_to_state = actionToState;
}

const std::vector<std::pair<State *, float >> &State::getStateToProbability() const {
    return state_to_probability;
}

void State::setStateToProbability(const std::vector<std::pair<State *, float >> &stateToProbability) {
    state_to_probability = stateToProbability;
}
