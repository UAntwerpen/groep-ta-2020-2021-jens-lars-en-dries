//
// Created by driesdemaeseneer on 4/17/21.
//

#ifndef TO_GROEP_ACTION_H
#define TO_GROEP_ACTION_H

#include<vector>

class State;

class Action {
    // list mapping states to there transition chance
    std::vector<std::pair<State*, double>> chance_per_transition;

public:
    // comparing actions operator
    bool operator==(Action& action);

};


#endif //TO_GROEP_ACTION_H
