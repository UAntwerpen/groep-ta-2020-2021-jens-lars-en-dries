//
// Created by driesdemaeseneer on 4/15/21.
//

#include "State.h"

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

void State::setProbability(int in_action, float probability) {
    action_to_probability[in_action] = probability;
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

std::pair<int, int> State::getCoordinates() {
    return std::pair<int, int>(x, y);
}

State::State(const int in_x, const int in_y, std::vector<int> &in_actions) {
    x=in_x;
    y=in_y;
    actions = in_actions;
}

