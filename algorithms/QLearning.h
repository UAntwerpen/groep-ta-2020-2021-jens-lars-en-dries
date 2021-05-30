#ifndef TO_GROEP_QLEARNING_H
#define TO_GROEP_QLEARNING_H

#include <vector>
#include <tuple>
#include "../datastructures/State.h"
#include "../datastructures/Environment.h"
#include <stdio.h>
#include "../datastructures/LA.h"
#include "../random/Random.h"
#include "AbstractAgent.h"

class QLearning : AbstractAgent{
    float epsilon;
    float alpha;
    float gamma;
    // the learning automata
    LA la;

public:
    // constructor
    QLearning(Environment * env, float epsilon, float alpha, float gamma);
    // train for a given amount of episodes in a given environment using Q-learning
    void train(Environment& gridworld, int nr_episodes, int max_steps, int prints_every_epoch);
    std::vector<std::tuple<State*, int, float >> play(Environment& gridworld, int max_steps);

    void setEpsilon(float x){ epsilon = x;}
    LA getLA(){return la;};

    void save(string outfileName);
    void load(LA* savedLA);

private:
    void learn(State* current_state, int current_action, State* next_state, float reward);
};


#endif
