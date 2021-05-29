#include <complex>
#include "MCLearning.h"
#include "../datastructures/Environment.h"


void MCLearning::train(Environment& gridworld, int nr_episodes, int max_steps, int prints_every_epoch) {
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
        gridworld.reset();
        auto episode = play(gridworld, max_steps);
        // Progress bar
        if(i%prints_every_epoch==0) {
            printf("Processed episode (%02d/%02d) in %zu steps\n", i, nr_episodes, episode.size());
        }
        // Calculate cumulative reward of episode
        float cumulative_reward = 0;
        for(long unsigned int i = 0;i<episode.size();i++) cumulative_reward += std::get<2>(episode[i])*std::pow(discountfactor, i);
        // Loop over time steps in the i'th episode
        for(long unsigned int time_step = 0; time_step<episode.size(); time_step++){
            // get values from tuple.
            auto state = std::get<0>(episode[time_step]);
            int action = std::get<1>(episode[time_step]);
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
        learn();
    }
}

std::vector<std::tuple<State*, int, float>>  MCLearning::play(Environment& gridworld, int max_steps) {
     /*
      * the play method will use policy[time_step] to generate an episode.
      */


    // the resulting episode.
    std::vector<std::tuple<State*, int, float>> to_export;

    // initialize variables
    bool finished = false;

    // get start positions
    State* current_state = la.getStartState();

    // while exit not found
    while(!finished and to_export.size()<max_steps) {
        // pick action
        int current_action = la.pickAction(current_state);
        // get environment result
        auto result = gridworld.step(current_action);

        finished = std::get<2> (result);
        // add current state, action and reward tuple to the episode.
        to_export.emplace_back(std::make_tuple(current_state, current_action, std::get<1>(result)));
        // calculate the new state
        current_state = la.coordinatesToState(std::make_pair(std::get<0>(result)->x, std::get<0>(result)->y));
    }
    return to_export;
}

void MCLearning::learn() {
     /*
      * the learn method will become more greedy over time, this is useful to encourage exploration.
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

MCLearning::MCLearning(Environment &env, float in_epsilon) {
    la = this->la = LA(env.height, env.width, std::make_pair(env.start->x, env.start->y), env.actions);;
    epsilon = in_epsilon;
}

std::vector<int> MCLearning::getOptimalRoute(Environment &gridworld) {

    gridworld.reset();

    std::vector<int> to_export;

    State* current_state = la.getStartState();
    while(current_state->getCoordinates()!=std::make_pair(gridworld.end->x, gridworld.end->y) and to_export.size() < 100){
        int next_action = la.argmax(current_state);
        current_state = la.G(current_state, next_action);
        to_export.emplace_back(next_action);
    }
    return to_export;
}

void MCLearning::save(string outfileName) {
    la.save(outfileName);
}

void MCLearning::load(LA *savedLA) {
    la = *savedLA;
}

LA MCLearning::getLA() {
    return la;
}
