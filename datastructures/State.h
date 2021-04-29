//
// Created by driesdemaeseneer on 4/15/21.
//

#ifndef TO_GROEP_STATE_H
#define TO_GROEP_STATE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>


class State {
    // list of all actions
    std::vector<int> actions;

    // list of action values. it stores the value of a given action.
    std::map<int, float> Q_value;

    // list of action-state pairs. it stores the state corresponding with a given action.
    std::map<int, State*> action_to_state;

    // list of state-probability pairs. it stores the probability to transition to a given state.
    std::map<State*, float> state_to_probability;

    // action counter
    std::map<int, int> counter;

public:

    // get the action list
    const std::vector<int> &getActions() const;

    // set the action list
    void setActions(std::vector<int> &actions);
    // get the Q_value map
    const std::map<int, float> &getQValue() const;

    // set the Q_value map
    void setQValue(std::map<int, float> &value);

    // get the ActionToState map
    const std::map<int, State *> &getActionToState() const;

    // set the ActionToState map
    void setActionToState(std::map<int, State *> &actionToState);

    // get the StateToProbability map
    const std::map<State *, float > &getStateToProbability() const;

    // set the StateToProbability amp
    void setStateToProbability( std::map<State *, float > &stateToProbability);

    // set the value of an action
    void setValue(int action, float in_value);

    // get the value of an action
    float getValue(int action);

    // find corresponding state to an action
    State* operator[](const int action) const;

    void setProbability(State* in_state, float probability);

    // get action count
    int getActionCount(const int action);

    // increment the counter for a given action
    void incrementCounter(const int action);
};


#endif //TO_GROEP_STATE_H
