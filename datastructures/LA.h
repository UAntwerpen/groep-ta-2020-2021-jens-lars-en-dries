//
// Created by driesdemaeseneer on 4/15/21.
//

#ifndef TO_GROEP_LA_H
#define TO_GROEP_LA_H

#include <vector>
#include <limits>
#include "State.h"


class LA {
    std::vector<State*> all_states;
    std::vector<int> all_actions;
    State* start_state;

    std::vector<std::pair<std::pair<int,int>,State*>> coordinates_to_state;

public:
    void reset();

    /*
     * This function will return a
     */
    State *G(State *in_state, int in_action);

    /*
     * Argmax of in_state's Q_values.
     */
    int pickAction(State *in_state);

    /*
     * This function calculates the corresponding state to the given coordinates.
     */
    State* coordinatesToState(std::tuple<int,int> in_coords);

    /*
     * This function returns the start state.
     */
    State* getStartState() { return start_state; }

    std::vector<State*> getAllStates();

    std::vector<int> getAllActions();
};


#endif //TO_GROEP_LA_H
