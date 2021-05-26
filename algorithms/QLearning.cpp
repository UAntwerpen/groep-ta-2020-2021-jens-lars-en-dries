#include "QLearning.h"

QLearning::QLearning(Environment * env, float epsilon, float alpha, float gamma) {
    this->epsilon = epsilon;
    this->alpha = alpha;
    this->gamma = gamma;
    this->la = LA(env->height, env->width, std::make_pair(env->start->x, env->start->y), env->actions);
}

void QLearning::learn(State* current_state, int current_action, State* next_state, float reward) {
    // epsilon greedy policy update
    for(int action:current_state->getActions()){
        if(action == la.argmax(current_state)){
            current_state->setProbability(action, ((1-epsilon)+(epsilon/(float)current_state->getActions().size())));
        }
        else{
            current_state->setProbability(action, (epsilon/(float)current_state->getActions().size()));
        }
    }
    float next_Q = next_state->getValue(la.argmax(next_state));
    float new_Q = current_state->getValue(current_action)+alpha*(reward+gamma*next_Q-current_state->getValue(current_action));
    current_state->setValue(current_action, new_Q);
}

void QLearning::train(Environment * env, int nr_episodes, int max_steps, int prints_every_epoch) {
    State* current_state = la.getStartState();
    int episode = 0;
    int steps = 0;
    while(episode<nr_episodes){
        env->reset();
        if(episode%prints_every_epoch==0) {
            printf("Processed episode (%02d/%02d) in %zu steps\n", episode, nr_episodes, steps);
        }
        steps = 0;
        bool done = false;
        while(!done and steps<max_steps) {
            // pick an action
            int current_action = la.pickAction(current_state);
            // get state, reward from environment
            tuple<MDPState *, float, bool> state_reward_bool = env->step(current_action);
            // get next state
            State * next_state = la.coordinatesToState(std::make_pair(std::get<0>(state_reward_bool)->x, std::get<0>(state_reward_bool)->y));
            float reward = std::get<1>(state_reward_bool);
            // train from state, reward, action
            learn(current_state, current_action, next_state, reward);
            // update new state
            current_state = next_state;
            done = std::get<2>(state_reward_bool);
            steps += 1;
        }
        episode += 1;
    }
}

void QLearning::load(LA *savedLA) {
    la = *savedLA;
}
