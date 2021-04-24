////
//// Created by driesdemaeseneer on 4/15/21.
////
//
//#include <complex>
//#include "Agent.h"
//#include "Environment.h"
//
//
//void Agent::onPolicyImprove(int nr_episodes, Environment& gridworld) {
//    /*
//     *  the onPolicyImprove method will improve the agent's policy over nr_episodes episodes.
//     *  we use the GLIE Monte-Carlo Control to converge to the optimal action-Q_value function Q(s,a) -> q*(s,a).
//     *  the GLIE method will encourage exploration and overtime become more greedy to optimize the policy.
//     */
//
//    //init variables
//    // TODO: init vars
//
//    for(int i=0;i<nr_episodes;i++){
//        // Generate i'th episode
//        gridworld.reset();
//        auto episode = play(gridworld);
//
//        // Calculate cumulative reward of episode
//        float cumulative_reward = 0;
//        for(int i = 0;i<episode.size();i++) cumulative_reward += std::get<1>(episode[i])*std::pow(discountfactor, i);
//
//        // Loop over time steps in the i'th episode
//        for(int time_step = 0; time_step<episode.size(); time_step++){
//            // increpent counter
//            auto temp_pair = std::make_tuple(std::get<0>(episode[time_step]), std::get<1>(episode[time_step]));
//            auto state_action_pair = findStateActionCounter(temp_pair);
//            std::get<1>(state_action_pair)+=1;
//            // calculate new Q_values
//
//            auto state = std::get<0>(episode[time_step]);
//            int action = std::get<1>(episode[time_step]);
//            float reward = std::get<2>(episode[time_step]);
//            float value = state->getValue(action);
//            auto state_action_count = std::get<1>(findStateActionCounter(std::make_tuple(state, action)));
//            state->setValue(action, value + ((float)1/state_action_count) * (reward - value));
//
//        }
//        epsilon = (float)1/i;
//        policy = epsilon_greedy_policy_improvement();
//        // policy improvement
//        // TODO: update policy_i
//    }
//}
//
//std::vector<std::tuple<State*, int, float>>  Agent::play(Environment& gridworld) {
//    /*
//     * the play method will use polocy[time_step] to generate an episode.
//     */
//
//    // the resulting episode.
//    std::vector<std::tuple<State*, int, float>> to_export;
//    bool finished= false;
//    float reward;
//    int action_to_do;
//
//    // get start positions
//    State* current_state = la.getStartState();
//    std::tuple<int,int> enviroment_state = gridworld.start;
//
//    // while exit not found //TODO: max steps??
//    while(!finished) {
//        // find action with current policy.
//        for (auto &it: policy) if (it.first == current_state) action_to_do = it.second;
//        // step in the enviroment.
//        std::tuple<std::tuple<int, int>, float, bool> a = gridworld.step(action_to_do);
//        enviroment_state = std::get<0>(a);
//        reward = std::get<1>(a);
//        finished = std::get<2>(a);
//        current_state = la.coordinatesToState(enviroment_state);
//        // add the current_state, action and reward to episode.
//        to_export.emplace_back(std::make_tuple(current_state, action_to_do, reward));
//    }
//    return to_export;
//}
//
//std::tuple<std::tuple<State *, int>, int>& Agent::findStateActionCounter(std::tuple<State *, int> state_action_pair) {
//    for(auto& it: state_action_counter){
//        if(std::get<0>(it)==state_action_pair) return it;
//    }
//}
//
//std::map<State *, int> Agent::epsilon_greedy_policy_improvement() {
//    /*
//     * the epsilon_greedy_policy_improvement method will become more greedy over time, this is usefull to encourage exploration.
//     */
//
//    // include random source with automatic seed
//    Random random;
//    // initialize the return policy
//    std::map<State *, int> to_export;
//    // loop over all the states in the learning automata
//    for(auto& it:la.getAllStates()){
//
//        float random_percentage = (float)(random.rand()%10000)/10000;
//        // take a* (the optimal action in by value)
//        if((1-epsilon)+(epsilon/(float)la.getAllActions().size())>random_percentage){
//            to_export[it] = la.pickAction(it);
//        }
//        // else taken random a to encourage exploration
//        else{
//            to_export[it] = la.getAllActions()[random.rand()%la.getAllActions().size()];
//        }
//    }
//    return to_export;
//}
