#ifndef TO_GROEP_QLEARNING_H
#define TO_GROEP_QLEARNING_H

#include <vector>
#include <tuple>
#include "../datastructures/State.h"
#include "../datastructures/Environment.h"
#include <stdio.h>
#include "../datastructures/LA.h"
#include "../random/Random.h"

class QLearning {
    float epsilon;
    float alpha;
    float gamma;
    // the learning automata
    LA la;

public:
    // constructor
    QLearning(Environment * env, float epsilon, float alpha, float gamma);
    // learn for a given amount of episodes in a given environment using Q-learning
    void train(Environment * env, int nr_episodes, int max_steps, int prints_every_epoch);
    void setEpsilon(float x){ epsilon = x;}
private:
    void learn(State* current_state, int current_action, State* next_state, float reward);
};


#endif
