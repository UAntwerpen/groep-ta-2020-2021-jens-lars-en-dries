#ifndef TO_GROEP_LA_H
#define TO_GROEP_LA_H

#include <vector>
#include <limits>
#include "State.h"


class LA {

    LA* properly_init;

    int height;
    int width;

    std::vector<State*> all_states;

    std::vector<int> all_actions;

    State* start_state;

    std::map<std::pair<int,int>, State*> coordinates_to_state;

public:
    // default constructor
    LA();
    // complex constructor
    LA(const int height, const int width, std::pair<int, int> start_coordinates, std::vector<int>& actions);
    // destructor
//    ~LA();

    void reset();

    /*
     * This function will return the state corresponding with the state-action input.
     */
    State *G(State *in_state, int in_action);

    /*
     * Argmax of in_state's Q_values.
     */
    int pickAction(State *in_state);

    int argmax(State *in_state);

    /*
     * This function calculates the corresponding state to the given coordinates.
     */
    State* coordinatesToState(std::tuple<int,int> in_coords);

    /*
     * This function returns the start state.
     */
    State* getStartState() { return start_state; }

    /*
     *
     */
    void setStartState(State* startState){start_state = startState;}

    bool addState(State* newState);

    std::vector<State*> getAllStates();

    std::vector<int> getAllActions();

    void setAllActions(std::vector<int> new_AllActions){all_actions = new_AllActions;}

    void setWidth(int x){width = x;}

    void setHeight(int y){height = y;}

    // check if the automata is properly initialized
    bool isProperlyInitialized();

    bool save(std::string outputFileName);

    // reset all counters of all states
    void resetCounter();

    void setCoordMap(std::map<std::pair<int, int>, State*> inputMap){ coordinates_to_state = inputMap;}
};


#endif //TO_GROEP_LA_H
