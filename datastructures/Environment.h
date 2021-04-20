#ifndef TO_GROEP_ENVIRONMENT_H
#define TO_GROEP_ENVIRONMENT_H

#include <tuple>
#include <string>
#include <list>
#include <vector>
#include <map>

// The environment class follows the gym framework: https://gym.openai.com/docs/
class Environment {
public:
    int height;
    int width;
    int seed;
    bool deterministic;
    float living_reward;
    std::vector<std::tuple<int, int>> observable_states;
    std::tuple<int, int> start;
    // need the near_terminal for the final action -> terminal action is a loop outside of the gridworld (there's reasons for this).
    std::tuple<int, int> end;
    std::tuple<int, int> current_state;

    Environment(int height, int width, int seed, bool deterministic, float living_reward);

    // accepts: action (int), 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
    // returns: next_state (coordinates, tuple of ints), reward (float), done (bool)
    std::tuple<std::tuple<int, int>, float, bool> step(int action);

    // returns the start state
    std::tuple<int, int> reset();

    // returns the available actions for the specified state
    std::list<int> available_actions(std::tuple<int, int>);

    // dynamics function of the MDP for this state and action.
    // accepts a state and action
    // returns a map of: <tuple(state, reward), probability>
    std::map<std::tuple<std::tuple<int, int>, float>, float> p(std::tuple<int, int> state, int action);

    // to check whether a state is the end (terminal) state
    bool is_terminal(std::tuple<int, int>);

    // render the environment
    void render();

    // return a list of all states in the environment
    std::list<std::tuple<int, int>> states();

private:
    // dynamics of the environment: a map of <(state, action): map<(state, reward), probability>
    std::map<std::tuple<std::tuple<int, int>, int>, std::map<std::tuple<std::tuple<int, int>, float>, float>> dynamics;

    // used for populating the world
    void generate_world();

    bool check_obstacle(std::tuple<int, int> state, std::vector<std::tuple<int, int>> obstacles);
};


#endif //TO_GROEP_ENVIRONMENT_H
