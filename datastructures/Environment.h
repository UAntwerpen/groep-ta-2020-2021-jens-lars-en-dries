#ifndef TO_GROEP_ENVIRONMENT_H
#define TO_GROEP_ENVIRONMENT_H

#include <tuple>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <random>
#include <stack>
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
    float lava_reward = -100.0;
    float end_reward;
    float percentage_obstacles;
    float drifting_away_chance = 0.3;
    vector<MDPState> states;
    MDPState* start;
    MDPState* end;
    MDPState* curr_state;
    tuple<int, int > startcoords;
    // a gridworld accepts following actions (int): 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
    std::vector<int> actions = {0, 1, 2, 3};

    Environment(int height, int width, int seed, bool deterministic, float living_reward, float end_reward, float percentage_obstacles);

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

    std::stack<MDPState> runDijkstra();

private:
    // used for populating the world
    void generate_world();
    void generate_deterministic_world();
    void generate_non_deterministic_world();
    void generate_obstacles(float obst_percentage);
    void generate_non_deterministic_obstacles();
    // dynamics of the environment: a map of <(state, action): map<(state, reward), probability>
    map<tuple<MDPState *, int>, map<tuple<MDPState *, float>, float>> dynamics;
    void insert_deterministic_dynamics(MDPState *current_state, int action, MDPState* next_state);
    void insert_non_deterministic_dynamics(MDPState *current_state, int action, float reward, float probability, MDPState* next_state);
};


#endif //TO_GROEP_ENVIRONMENT_H
