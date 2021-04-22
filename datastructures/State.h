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
    std::vector<int> actions;
    // list of action values
    std::vector<std::pair<int, float>> Q_value;
    // list of action-state pairs
    std::vector<std::pair<int, State*>> action_to_state;
    // list of state-probability pairs
    std::vector<std::pair<State*, float>> state_to_probability;
public:
    // getters and setters
    const std::vector<int> &getActions() const;
    void setActions(const std::vector<int> &actions);
    const std::vector<std::pair<int, float>> &getQValue() const;
    void setValue1(const std::vector<std::pair<int, float>> &value);
    const std::vector<std::pair<int, State *>> &getActionToState() const;
    void setActionToState(const std::vector<std::pair<int, State *>> &actionToState);
    const std::vector<std::pair<State *, float>> &getStateToProbability() const;

    void setStateToProbability(const std::vector<std::pair<State *, float>> &stateToProbability);

    // find corresponding state to an action
    State* operator[](int action) const;
    // find corresponding probability to a state
    float operator[](State* state) const;

    void setValue(int action, float in_value);

    float getValue(int action);

    std::pair<int, float>& findActionValuePair(int action);

    float pToState(State* in_state);

};


#endif //TO_GROEP_STATE_H
