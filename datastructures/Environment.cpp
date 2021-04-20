#include "Environment.h"

Environment::Environment(int height, int width, int seed, bool deterministic, float living_reward,
                         float percentage_obstacles) {
    this->width = width;
    this->height = height;
    this->seed = seed;
    this->deterministic = deterministic;
    this->living_reward = living_reward;
    this->percentage_obstacles = percentage_obstacles;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            observable_states.push_back(std::tuple<int, int>{x, y});
        }
    }
    srand(seed);
    int start_x = rand() % width;
    int start_y = rand() % height;
    start = {start_x, start_y};
    do {
        int end_x = rand() % width;
        int end_y = rand() % height;
        this->end = {end_x, end_y};
    } while (start == end);
    current_state = start;
    generate_world();
}

void Environment::generate_world() {
    srand(this->seed);
    if (deterministic) {
        // generate obstacles, 20% of gridworld are obstacles / mountains
        int n_obstacles = (width * height) * percentage_obstacles;
        std::vector<std::tuple<int, int>> obstacles;
        int x, y;
        while (n_obstacles > 0) {
            x = rand() % width;
            y = rand() % height;
            std::tuple<int, int> state_(x, y);
            // todo need to check if there exists a path between start and end -> otherwise create a new obstacle and check again
            if (start != state_ && end != state_) {
                obstacles.push_back(state_);
                n_obstacles -= 1;
            }
        }
        for (auto const &[x, y] : observable_states) {
            // todo end state needs special transition -> at end, set end state action to special state
            // dynamics of the environment: a map of <(state, action): map<(state, reward), probability>
            // accepts: action (int), 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
            if (y + 1 >= height || check_obstacle({x, y + 1}, obstacles)) {
                // check bounds of environment -> if actions leads outside bounds, stay put
                std::tuple<int, int> next_state_(x, y);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 0);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            } else {
                std::tuple<int, int> next_state_(x, y + 1);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 0);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            }
            if (y - 1 < 0 || this->check_obstacle({x, y - 1}, obstacles)) {
                // check bounds of environment -> if actions leads outside bounds, stay put
                std::tuple<int, int> next_state_(x, y);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 2);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            } else {
                std::tuple<int, int> next_state_(x, y - 1);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 2);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            }
            if (x + 1 >= width || check_obstacle({x + 1, y}, obstacles)) {
                // check bounds of environment -> if actions leads outside bounds, stay put
                std::tuple<int, int> next_state_(x, y);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 1);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            } else {
                std::tuple<int, int> next_state_(x + 1, y);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 1);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            }
            if (x - 1 < 0 || this->check_obstacle({x - 1, y}, obstacles)) {
                // check bounds of environment -> if actions leads outside bounds, stay put
                std::tuple<int, int> next_state_(x, y);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 3);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            } else {
                std::tuple<int, int> next_state_(x - 1, y);
                std::tuple<std::tuple<int, int>, float> next_state_reward(next_state_, living_reward);
                std::map<std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                std::tuple<int, int> current_state_(x, y);
                std::tuple<std::tuple<int, int>, int> current_state_action(current_state_, 3);

                dynamics.insert(std::make_pair(current_state_action, state_reward_prob));
            }
        }
    } else {
        // Nondeterministic world generation
    }
}

std::map<std::tuple<std::tuple<int, int>, float>, float> Environment::p(std::tuple<int, int> state, int action) {
    std::tuple<std::tuple<int, int>, int> current_state_action(state, action);
    return dynamics[current_state_action];
}

bool Environment::check_obstacle(std::tuple<int, int> state, std::vector<std::tuple<int, int>> obstacles) {
    if (std::find(obstacles.begin(), obstacles.end(), state) != obstacles.end()) {
        return true;
    }
    return false;
}
