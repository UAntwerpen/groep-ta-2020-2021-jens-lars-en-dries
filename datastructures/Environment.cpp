#include <algorithm>
#include "Environment.h"
#include "../random/Random.h"
#include "../parser/tinyxml/tinyxml.h"
#include <sstream>

Environment::Environment(int height, int width, int seed, bool deterministic, float living_reward, float end_reward,
                         float percentage_obstacles) {
    this->width = width;
    this->height = height;
    this->seed = seed;
    this->deterministic = deterministic;
    this->living_reward = living_reward;
    this->end_reward = end_reward;
    this->percentage_obstacles = percentage_obstacles;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            MDPState state_ = MDPState(x, y, ".", false);
            states.push_back(state_);
        }
    }
    // todo rand -> random
    Random random(this->seed);
    srand(this->seed);
    int start_x = random.rand() % width;
    int start_y = random.rand() % height;
    start = get_state_by_coordinates(start_x, start_y);
    start->type = "S";
    do {
        int end_x = random.rand() % width;
        int end_y = random.rand() % height;
        this->end = get_state_by_coordinates(end_x, end_y);
    } while (start == end);
    end->type = "E";
    end->terminal = true;
    current_state = start;
    generate_world();
}

void Environment::generate_world() {
    if (deterministic) {
        generate_deterministic_world();
    } else {
        // Nondeterministic world generation
    }
}

void Environment::generate_deterministic_world() {
    generate_obstacles();
    for (auto &current_state: states) {
        int x = current_state.x;
        int y = current_state.y;
        MDPState *next_state = get_state_by_coordinates(x, y + 1);
        // check bounds of environment -> if actions leads outside bounds, stay put
        if (y + 1 >= height || next_state->type == "O") {
            next_state = get_state_by_coordinates(x, y);
            update_deterministic_dynamics(&current_state, 0, next_state);
        } else {
            next_state = get_state_by_coordinates(x, y + 1);
            update_deterministic_dynamics(&current_state, 0, next_state);
        }
        next_state = get_state_by_coordinates(x, y - 1); // hier loopt iets fout.c
        if (y - 1 < 0 || next_state->type == "O") {
            next_state = get_state_by_coordinates(x, y);
            update_deterministic_dynamics(&current_state, 2, next_state);
        } else {
            next_state = get_state_by_coordinates(x, y - 1);
            update_deterministic_dynamics(&current_state, 2, next_state);
        }
        next_state = get_state_by_coordinates(x + 1, y);
        if (x + 1 >= width || next_state->type == "O") {
            next_state = get_state_by_coordinates(x, y);
            update_deterministic_dynamics(&current_state, 1, next_state);
        } else {
            next_state = get_state_by_coordinates(x + 1, y);
            update_deterministic_dynamics(&current_state, 1, next_state);
        }
        next_state = get_state_by_coordinates(x - 1, y);
        if (x - 1 < 0 || next_state->type == "O") {
            next_state = get_state_by_coordinates(x, y);
            update_deterministic_dynamics(&current_state, 3,next_state);
        } else {
            next_state = get_state_by_coordinates(x - 1, y);
            update_deterministic_dynamics(&current_state, 3, next_state);
        }
    }
}

void Environment::generate_obstacles() {
    int n_obstacles = (width * height) * percentage_obstacles;
    int x, y;
    Random random(this->seed);
    while (n_obstacles > 0) {
        x = random.rand() % width;
        y = random.rand() % height;
        MDPState *state_ = get_state_by_coordinates(x, y);
        // todo need to check if there exists a path between start and end -> otherwise create a new obstacle and check again
        if ((start->x != state_->x || start->y != state_->y) && (end->y != state_->y || end->x != state_->x)) {
            // set the state type to obstacle (O)
            state_->type = "O";
            n_obstacles -= 1;
        }
    }
}

map<tuple<MDPState *, float>, float> Environment::p(MDPState *state, int action) {
    tuple<MDPState *, int> current_state_action(state, action);
    return dynamics[current_state_action];
}

MDPState *Environment::get_state_by_coordinates(int x, int y) {
    for (int i = 0; i < states.size(); i++) {
        if (states[i].x == x && states[i].y == y) {
            return &states[i];
        }
    }
    return nullptr;
}

void Environment::update_deterministic_dynamics(MDPState *current_state, int action, MDPState *next_state) {
    float reward = living_reward;
    if (next_state == end) {
        reward = end_reward;
    }
    tuple<MDPState *, float> next_state_reward(next_state, reward);
    map<tuple<MDPState *, float>, float> state_reward_prob = {{next_state_reward, 1.0}};
    tuple<MDPState *, int> current_state_action(current_state, action);
    dynamics.insert(make_pair(current_state_action, state_reward_prob));
}

MDPState *Environment::reset() {
    this->current_state = this->start;
    return this->current_state;
}

void Environment::render() {
    string output;
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            MDPState *state = get_state_by_coordinates(x, y);
            string state_r = state->type;
            if (current_state == state) {
                // current state is designated by an "X" in the gridworld.
                state_r = "X";
            }
            output += state_r + "|";
        }
        output += "\n";
    }
    cout << output;
}

tuple<MDPState *, float, bool> Environment::step(int action) {
    // get distributions according to environment dynamics (current state and action chosen by agent)
    map<tuple<MDPState *, float>, float> distributions = p(current_state, action);
    std::vector<tuple<MDPState *, float>> state_rewards;
    std::vector<float> probabilities;
    for (auto const &distribution: distributions) {
        state_rewards.push_back(distribution.first);
        probabilities.push_back(distribution.second);
    }
    // sampling according to distributions
    std::random_device rd;
    std::mt19937 gen(rd());
    discrete_distribution<> d(probabilities.begin(), probabilities.end());
    tuple<MDPState *, float> next_state_reward = state_rewards[d(gen)];
    // We've chosen a new state according to the probabilities (dynamics)
    current_state = get<0>(next_state_reward);
    // checking for terminal state
    bool done = current_state->terminal;
    // returns: next_state (MDPState), reward (float), done (bool)
    tuple<MDPState *, float, bool> state_reward_bool = tuple_cat(next_state_reward, make_tuple(done));
    return state_reward_bool;
}

bool Environment::save(std::string outputFileName) {
    stringstream s;
    // Create root.
    TiXmlDocument doc;
    TiXmlElement* root = new TiXmlElement("Environment");
    doc.LinkEndChild(root);

    TiXmlElement* width_segment = new TiXmlElement("width");
    root->LinkEndChild(width_segment);
    s << width;
    TiXmlText* width_txt = new TiXmlText(s.str().c_str());
    width_segment->LinkEndChild(width_txt);
    s.str("");

    TiXmlElement* height_segment = new TiXmlElement("height");
    root->LinkEndChild(height_segment);
    s << height;
    TiXmlText* height_txt = new TiXmlText(s.str().c_str());
    height_segment->LinkEndChild(height_txt);
    s.str("");

    TiXmlElement* seed_segment = new TiXmlElement("seed");
    root->LinkEndChild(seed_segment);
    s << seed;
    TiXmlText* seed_txt = new TiXmlText(s.str().c_str());
    seed_segment->LinkEndChild(seed_txt);
    s.str("");

    TiXmlElement* deterministic_segment = new TiXmlElement("deterministic");
    root->LinkEndChild(deterministic_segment);
    s << deterministic;
    TiXmlText* deterministic_txt = new TiXmlText(s.str().c_str());
    deterministic_segment->LinkEndChild(deterministic_txt);
    s.str("");

    TiXmlElement* livingreward_segment = new TiXmlElement("livingreward");
    root->LinkEndChild(livingreward_segment);
    s << living_reward;
    TiXmlText* livingreward_txt = new TiXmlText(s.str().c_str());
    livingreward_segment->LinkEndChild(livingreward_txt);
    s.str("");

    TiXmlElement* endreward_segment = new TiXmlElement("endreward");
    root->LinkEndChild(endreward_segment);
    s << end_reward;
    TiXmlText* endreward_txt = new TiXmlText(s.str().c_str());
    endreward_segment->LinkEndChild(endreward_txt);
    s.str("");

    TiXmlElement* percentageobstacles_segment = new TiXmlElement("percentageobstacles");
    root->LinkEndChild(percentageobstacles_segment);
    s << percentage_obstacles;
    TiXmlText* percentageobstacles_txt = new TiXmlText(s.str().c_str());
    percentageobstacles_segment->LinkEndChild(percentageobstacles_txt);
    s.str("");

    doc.SaveFile(("data/" + outputFileName).c_str());
    return true;
}


