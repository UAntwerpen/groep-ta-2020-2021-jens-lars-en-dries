//
// Created by driesdemaeseneer on 4/15/21.
//

#ifndef TO_GROEP_AGENT_H
#define TO_GROEP_AGENT_H

#include <vector>
#include <tuple>
#include "State.h"
#include "Environment.h"
#include "LA.h"
#include "../random/Random.h"

class Agent {

    // epsilon is the infinite exploration part of GLIE. It will asymptotically increase the greediness of the policy.
    float epsilon;

    // the discount factor
    const float discountfactor = 1;

    // the learning automata
    LA la;

public:
    // constructor
    Agent(LA& in_la, float in_epsilon);

    // learn for a given amount of episodes in a given environment
    void learn(int nr_episodes, Environment& gridworld);

    // Play an episode in the enviroment
    std::vector<std::tuple<State*, int, float >> play(Environment& gridworld);

    // improve the policy of the LA
    void epsilon_greedy_policy_improvement();

    void setEpsilon(float x){ epsilon = x;}

    // get the optimal route
    std::vector<int> getOptimalRoute(Environment& gridworld);
};


#endif //TO_GROEP_AGENT_H
