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
    // coordinates of the state
    int x;
    int y;

    // list of all actions
    std::vector<int> actions;

    // list of action values. it stores the value of a given action.
    std::map<int, float> Q_value;

    // list  of action-probability pairs. it stores the probability to take a given action.
    std::map<int, float> action_to_probability;

    // action counter
    std::map<int, int> counter;

public:
    // constructor
    State(int in_x,int in_y, std::vector<int>& in_actions);

    // get the action list
    const std::vector<int> &getActions() const;

    // set the action list
    void setActions(std::vector<int> &actions);
    // get the Q_value map
    const std::map<int, float> &getQValue() const;

    // set the Q_value map
    void setQValue(std::map<int, float> &value);

    // set the value of an action
    void setValue(int action, float in_value);

    // get the value of an action
    float getValue(int action);

    void setProbability(int in_action, float probability);

    // get action count
    int getActionCount(const int action);

    // increment the counter for a given action
    void incrementCounter(const int action);

    std::pair<int, int> getCoordinates();

    void resetCounter();

};


#endif //TO_GROEP_STATE_H
