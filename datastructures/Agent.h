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
    // This agent will use GLIE Monte-Carlo Control to converge to the optimal action-Q_value function Q(s,a) -> q*(s,a)
    std::vector<std::tuple<std::tuple<State*, int>, int>> state_action_counter;
    // q*(s,a)
    std::map<State*, int> policy;
    // epsilon is the infinite exploration part of GLIE. It will asymptotically increase the greediness of the policy.
    float epsilon;

    const float discountfactor = 0.9;

    LA la;

public:

    void onPolicyImprove(int nr_episodes, Environment& gridworld);

    // Play an episode in the enviroment.
    std::vector<std::tuple<State*, int, float >> play(Environment& gridworld);

    // find the counter of an state-action pair.
    std::tuple<std::tuple<State*, int>, int>& findStateActionCounter(std::tuple<State*, int> state_action_pair);

    std::map<State *, int> epsilon_greedy_policy_improvement();

};


#endif //TO_GROEP_AGENT_H
