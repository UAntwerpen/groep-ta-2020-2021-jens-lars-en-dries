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

double State::operator[](State *state) const {
    for(auto& it:state_to_probability){
        if(&it.first == &state){
            return it.second;
        }
    }
    return 0;
}

void State::setValue(int action, double in_value) {
    findActionValuePair(action).second = in_value;
}

std::pair<int, double> &State::findActionValuePair(int action) {
    for(auto& it: value){
        if(it.first == action){
            return it;
        }
    }
}

double State::getValue(int action){
    for(auto& it: value){
        if(it.first == action){
            return it.second;
        }
    }
}

double State::pToState(State *in_state) {
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

const std::vector<std::pair<int, double>> &State::getValue1() const {
    return value;
}

void State::setValue1(const std::vector<std::pair<int, double>> &value) {
    State::value = value;
}

const std::vector<std::pair<int, State *>> &State::getActionToState() const {
    return action_to_state;
}

void State::setActionToState(const std::vector<std::pair<int, State *>> &actionToState) {
    action_to_state = actionToState;
}

const std::vector<std::pair<State *, double>> &State::getStateToProbability() const {
    return state_to_probability;
}

void State::setStateToProbability(const std::vector<std::pair<State *, double>> &stateToProbability) {
    state_to_probability = stateToProbability;
}
