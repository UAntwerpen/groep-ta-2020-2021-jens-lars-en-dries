#include <algorithm>
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
            MDPState state_ = MDPState(x, y, ".", false);
            states.push_back(state_);
        }
    }
    // todo rand -> random
    srand(this->seed);
    int start_x = rand() % width;
    int start_y = rand() % height;
    start = get_state_by_coordinates(start_x, start_y);
    do {
        int end_x = rand() % width;
        int end_y = rand() % height;
        this->end = get_state_by_coordinates(end_x, end_y);
    } while (start == end);
    current_state = start;
    generate_world();
}

void Environment::generate_world() {
    if (deterministic) {
        int n_obstacles = (width * height) * percentage_obstacles;
        int x, y;
        while (n_obstacles > 0) {
            x = rand() % width;
            y = rand() % height;
            MDPState * state_ = get_state_by_coordinates(x, y);
            // todo need to check if there exists a path between start and end -> otherwise create a new obstacle and check again
            if ((start->x != state_->x || start->y != state_->y) && (end->y != state_->y || end->x != state_->x)) {
                // set the state type to obstacle (O)
                state_->type = "O";
                n_obstacles -= 1;
            }
        }
        for (auto & current_state: states) {
            // todo end state needs special transition -> at end, set end state action to special state
            // check bounds of environment -> if actions leads outside bounds, stay put
            x = current_state.x;
            y = current_state.y;
            MDPState *next_state = get_state_by_coordinates(x, y + 1);
            if (y + 1 >= height || next_state->type == "O") {
                next_state = get_state_by_coordinates(x, y);
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 0);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            } else {
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 0);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            }
            next_state = get_state_by_coordinates(x, y - 1);
            if (y - 1 < 0 || next_state->type == "O") {
                next_state = get_state_by_coordinates(x, y);
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 2);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            } else {
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 2);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            }
            next_state = get_state_by_coordinates(x + 1, y);
            if (x + 1 >= width || next_state->type == "O") {
                next_state = get_state_by_coordinates(x, y);
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 1);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            } else {
                next_state = get_state_by_coordinates(x, y);
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 1);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            }
            next_state = get_state_by_coordinates(x - 1, y);
            if (x - 1 < 0 || next_state->type == "O") {
                next_state = get_state_by_coordinates(x, y);
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 3);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            } else {
                tuple<MDPState *, float> next_state_reward(next_state, living_reward);
                map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};

                tuple<MDPState *, int> current_state_action(&current_state, 3);

                dynamics.insert(make_pair(current_state_action, state_reward_prob));
            }
        }
    } else {
        // Nondeterministic world generation
    }
}

map<tuple<MDPState *, float>, float> Environment::p(MDPState * state, int action) {
    tuple<MDPState *, int> current_state_action(state, action);
    return dynamics[current_state_action];
}

MDPState * Environment::get_state_by_coordinates(int x, int y) {
    for (int i = 0; i < states.size(); i++)
    {
        if (states[i].x == x && states[i].y == y) {
            return &states[i];
        }
    }
}


