#ifndef TO_GROEP_MCLEARNING_H
#define TO_GROEP_MCLEARNING_H

#include <vector>
#include <tuple>
#include "../datastructures/State.h"
#include "../datastructures/Environment.h"
#include <stdio.h>
#include "../datastructures/LA.h"
#include "../random/Random.h"

class MCLearning {

    // epsilon is the infinite exploration part of GLIE. It will asymptotically increase the greediness of the policy.
    float epsilon;

    // the discount factor
    float discountfactor = 1;

    // the learning automata
    LA la;

public:
    // constructor
    MCLearning(Environment &env, float in_epsilon);

    // train for a given amount of episodes in a given environment using MC control
    void train(Environment& gridworld, int nr_episodes, int max_steps, int prints_every_epoch);

    // Play an episode in the enviroment
    std::vector<std::tuple<State*, int, float >> play(Environment& gridworld, int max_steps);

    // improve the policy of the LA
    void learn();

    void setEpsilon(float x){ epsilon = x;}

    void save();

    void load(LA* savedLA);

    LA getLA();

    // get the optimal route
    std::vector<int> getOptimalRoute(Environment& gridworld);
};


#endif //TO_GROEP_MCLEARNING_H
