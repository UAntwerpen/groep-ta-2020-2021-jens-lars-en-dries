#ifndef TO_GROEP_ENVIRONMENT_H
#define TO_GROEP_ENVIRONMENT_H

#include <tuple>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <random>
#include "../random/Random.h"
#include "MDPState.h"

using namespace std;
// The environment class follows the gym framework: https://gym.openai.com/docs/
class Environment {
public:
    int height;
    int width;
    int seed;
    bool deterministic;
    float living_reward;
    float end_reward;
    float percentage_obstacles;
    vector<MDPState> states;
    MDPState* start;
    // need the near_terminal for the final action -> terminal action is a loop outside of the gridworld (there's reasons for this).
    MDPState* end;
    MDPState* current_state;

    Environment(int height, int width, int seed, bool deterministic, float living_reward, float end_reward, float percentage_obstacles);

    // accepts: action (int), 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
    // returns: next_state (MDPState), reward (float), done (bool)
    tuple<MDPState *, float, bool> step(int action);

    // returns the start state and resets the environment
    MDPState * reset();

    // dynamics function of the MDP for this state and action.
    // accepts a state and action
    // returns a map of: <tuple(state, reward), probability>
    map<tuple<MDPState *, float>, float> p(MDPState * state, int action);

    // render the environment
    void render();
    // get a state pointer based on the coordinates
    MDPState * get_state_by_coordinates(int x, int y);

    bool save(std::string outputFileName);

private:
    // used for populating the world
    void generate_world();
    void generate_deterministic_world();
    void generate_obstacles();
    // dynamics of the environment: a map of <(state, action): map<(state, reward), probability>
    map<tuple<MDPState *, int>, map<tuple<MDPState *, float>, float>> dynamics;
    void update_deterministic_dynamics(MDPState *current_state, int action, MDPState* next_state);
};


#endif //TO_GROEP_ENVIRONMENT_H
