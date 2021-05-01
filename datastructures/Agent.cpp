//
// Created by driesdemaeseneer on 4/15/21.
//

#include <complex>
#include "Agent.h"
#include "Environment.h"


void Agent::learn(int nr_episodes, Environment& gridworld) {
    /*
     *  the onPolicyImprove method will improve the agent's policy over nr_episodes episodes.
     *  we use the GLIE Monte-Carlo Control to converge to the optimal action-Q_value function Q(s,a) -> q*(s,a).
     *  the GLIE method will encourage exploration and overtime become more greedy to optimize the policy.
     */

    //init variables
    // TODO: init vars

    std::cout<<"Learning, please wait a moment...\n";

    for(int i=0;i<nr_episodes;i++){

        // Generate i'th episode
        la.resetCounter();

        gridworld.reset();
        auto episode = play(gridworld);

        // Calculate cumulative reward of episode
        float cumulative_reward = 0;
        for(int i = 0;i<episode.size();i++) cumulative_reward += std::get<2>(episode[i])*std::pow(discountfactor, i);

        // Loop over time steps in the i'th episode
        for(int time_step = 0; time_step<episode.size(); time_step++){

            // get values from tuple.
            auto state = std::get<0>(episode[time_step]);
            int action = std::get<1>(episode[time_step]);
            float reward = std::get<2>(episode[time_step]);

            // increment counter.
            state->incrementCounter(action);
            // get current action value
            float value = state->getValue(action);
            // get action counter.
            int state_action_count = state->getActionCount(action);

            // calculate new Q_value for action action in the current state
            state->setValue(action, value + ((float)(cumulative_reward - value)/(float)state_action_count));

        }

        // policy improvement
        epsilon_greedy_policy_improvement();
    }
}

std::vector<std::tuple<State*, int, float>>  Agent::play(Environment& gridworld) {
     /*
      * the play method will use polocy[time_step] to generate an episode.
      */


    // the resulting episode.
    std::vector<std::tuple<State*, int, float>> to_export;

    // initialize variables
    bool finished = false;

    // get start positions
    State* current_state = la.getStartState();
    MDPState* enviroment_state = gridworld.start;

    // while exit not found //TODO: max steps??
    while(!finished and to_export.size()<100) {
        // pick action
        int current_action = la.pickAction(current_state);
        // get enviroment result
        auto result = gridworld.step(current_action);

        finished = std::get<2> (result);
        // add current state, action and reward tuple to the episode.
        to_export.emplace_back(std::make_tuple(current_state, current_action, std::get<1>(result)));
        // calculate the new state
        current_state = la.coordinatesToState(std::make_pair(std::get<0>(result)->x, std::get<0>(result)->y));
    }
    return to_export;
}

void Agent::epsilon_greedy_policy_improvement() {
     /*
      * the epsilon_greedy_policy_improvement method will become more greedy over time, this is useful to encourage exploration.
      * Reinforcement Learning: An Introduction second edition, 5.4 Monte Carlo Control without Exploring Starts p 124.
      */

    // loop over all the states in the learning automata
    for(auto& it:la.getAllStates()){
        for(int action:it->getActions()){

            // if 'action' is the argmax action of the current state, give it a transition probability of 1-e + e/|A(s)|
            if(action == la.argmax(it)){
                it->setProbability(action, ((1-epsilon)+(epsilon/(float)it->getActions().size())));
            }
            // else give this action a probability of e/|A(s)|.
            else{
                it->setProbability(action, (epsilon/(float)it->getActions().size()));
            }
        }
    }
}

Agent::Agent(LA &in_la, float in_epsilon) {
    la = in_la;
    epsilon = in_epsilon;
}
