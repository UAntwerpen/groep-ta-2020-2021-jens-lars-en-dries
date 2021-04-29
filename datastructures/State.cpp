//
// Created by driesdemaeseneer on 4/15/21.
//

#include "State.h"

State *State::operator[](const int action) const {
    for(auto& it:action_to_state){
        if(it.first == action){
            return it.second;
        }
    }
    return nullptr;
}


void State::setValue(int action, float in_value) {
    Q_value[action] = in_value;
}

float State::getValue(int action){
    return Q_value[action];
}


const std::vector<int> &State::getActions() const {
    return actions;
}

void State::setActions(std::vector<int> &actions) {
    State::actions = actions;
}

const std::map<int, float> &State::getQValue() const {
    return Q_value;
}

const std::map<int, State *> &State::getActionToState() const {
    return action_to_state;
}

void State::setActionToState(std::map<int, State *> &actionToState) {
    action_to_state = actionToState;
}

const std::map<State *, float > &State::getStateToProbability() const {
    return state_to_probability;
}

void State::setStateToProbability( std::map<State *, float > &stateToProbability) {
    state_to_probability = stateToProbability;
}

void State::setProbability(State *in_state, float probability) {
    state_to_probability[in_state] = probability;
}

void State::setQValue(std::map<int, float> &value) {
    Q_value = value;
}

int State::getActionCount(const int action) {
    return counter[action];
}

void State::incrementCounter(const int action) {
    counter[action]+=1;
}

