//
// Created by driesdemaeseneer on 4/15/21.
//

#ifndef TO_GROEP_STATE_H
#define TO_GROEP_STATE_H

#include <vector>
#include <string>
#include <iostream>


class State {
    // list of all actions
    std::vector<std::string> actions;
    // list of action-state pairs
    std::vector<std::pair<std::string, State*>> action_to_state;
    // list of state-probability pairs
    std::vector<std::pair<State*, double>> state_to_probability;
    // list of state-reward pairs
    std::vector<std::pair<State*, double>> state_to_reward;

public:
    // find corresponding state to an action
    State* operator[](std::string action) const;
    // find corresponding probability to a state //TODO: probability or reward?
    double operator[](State* state) const;

};


#endif //TO_GROEP_STATE_H
