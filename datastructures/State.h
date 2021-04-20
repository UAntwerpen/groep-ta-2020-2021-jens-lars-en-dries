//
// Created by driesdemaeseneer on 4/15/21.
//

#ifndef TO_GROEP_STATE_H
#define TO_GROEP_STATE_H

#include <vector>
#include <string>
#include <iostream>
#include "Action.h"


class State {
    // list of all actions
    std::vector<Action> actions;
    // list of action-state pairs
    std::vector<std::pair<Action, State*>> action_to_state;
    // list of state-probability pairs
    std::vector<std::pair<State*, double>> state_to_probability;

public:
    // find corresponding state to an action
    State* operator[](Action action) const;
    // find corresponding probability to a state
    double operator[](State* state) const;

};


#endif //TO_GROEP_STATE_H
