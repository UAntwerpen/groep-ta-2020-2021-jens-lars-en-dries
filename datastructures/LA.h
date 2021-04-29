//
// Created by driesdemaeseneer on 4/15/21.
//

#ifndef TO_GROEP_LA_H
#define TO_GROEP_LA_H

#include <vector>
#include <limits>
#include "State.h"


class LA {

    int height;
    int width;

    std::vector<State*> all_states;

    std::vector<int> all_actions;

    State* start_state;

    std::map<std::pair<int,int>, State*> coordinates_to_state;

public:

    LA(const int height, const int width, std::pair<int, int> start_coordinates, std::vector<int>& actions);

    ~LA();

    void reset();

    /*
     * This function will return the state corresponding with the state-action input.
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
