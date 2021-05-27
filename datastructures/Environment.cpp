#include <algorithm>
#include "Environment.h"
#include "../random/Random.h"
#include "../parser/tinyxml/tinyxml.h"
#include "../procederual-generation/RiverBezier.h"
#include "../procederual-generation/LavaPools.h"
#include <sstream>
#include <limits>
#include <stack>

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
    Random random;
    if (this->seed != -1) random.setSeed(this->seed);
    int start_x = random.rand() % width;
    int start_y = random.rand() % height;
    startcoords = tuple(start_x, start_y);
    start = get_state_by_coordinates(start_x, start_y);
    start->symbol = "S";
    do {
        int end_x = random.rand() % width;
        int end_y = random.rand() % height;
        this->end = get_state_by_coordinates(end_x, end_y);
    } while (start == end);
    end->symbol = "E";
    end->terminal = true;
    curr_state = start;
    generate_world();
}

void Environment::generate_world() {
    if (deterministic) {
        generate_deterministic_world();
    } else {
        generate_non_deterministic_world();
    }
}

void Environment::generate_deterministic_world() {
    generate_obstacles(percentage_obstacles);
    for (auto &current_state: states) {
        int x = current_state.x;
        int y = current_state.y;
        MDPState *next_state = get_state_by_coordinates(x, y + 1);
        // check bounds of environment -> if actions leads outside bounds, stay put
        if (y + 1 >= height || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
            insert_deterministic_dynamics(&current_state, 0, next_state);
        } else {
            next_state = get_state_by_coordinates(x, y + 1);
            insert_deterministic_dynamics(&current_state, 0, next_state);
        }
        next_state = get_state_by_coordinates(x, y - 1);
        if (y - 1 < 0 || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
            insert_deterministic_dynamics(&current_state, 2, next_state);
        } else {
            next_state = get_state_by_coordinates(x, y - 1);
            insert_deterministic_dynamics(&current_state, 2, next_state);
        }
        next_state = get_state_by_coordinates(x + 1, y);
        if (x + 1 >= width || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
            insert_deterministic_dynamics(&current_state, 1, next_state);
        } else {
            next_state = get_state_by_coordinates(x + 1, y);
            insert_deterministic_dynamics(&current_state, 1, next_state);
        }
        next_state = get_state_by_coordinates(x - 1, y);
        if (x - 1 < 0 || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
            insert_deterministic_dynamics(&current_state, 3, next_state);
        } else {
            next_state = get_state_by_coordinates(x - 1, y);
            insert_deterministic_dynamics(&current_state, 3, next_state);
        }
    }
}

void Environment::generate_obstacles(float obst_percentage) {
    if(obst_percentage > 0.31){
        cerr << "Cannot generate environment with obstacle percentage > 0.3.";
        return;
    }
    int n_obstacles = (width * height) * obst_percentage;
    int temp = n_obstacles;
    int x, y;
    Random random(this->seed);
    while(true){
        n_obstacles = temp;
        while (n_obstacles > 0) {
            x = random.rand() % width;
            y = random.rand() % height;
            MDPState *state_ = get_state_by_coordinates(x, y);
            if ((start->x != state_->x || start->y != state_->y) && (end->y != state_->y || end->x != state_->x)) {
                // set the state symbol to obstacle (O)
                state_->symbol = "O";
                n_obstacles -= 1;
            }
        }
        auto pathstack = runDijkstra();
        if(pathstack.size() == 0){
            for(auto state : states){
                if(state.symbol == "O"){
                    state.symbol = ".";
                }
            }
            cout << "Redoing obstacle generation..." << std::endl;
            continue;
        }
        break;
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

void Environment::insert_deterministic_dynamics(MDPState *current_state, int action, MDPState *next_state) {
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
    this->curr_state = this->start;
    return this->curr_state;
}

void Environment::render() {
    string output;
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            MDPState *state = get_state_by_coordinates(x, y);
            string state_r = state->symbol;
            if (curr_state == state) {
                // current state is designated by an "X" in the gridworld.
                state_r = "X";
            }
            output += state_r + "|";
        }
        output += "\n";
    }
    cout << output << "\n";
}

tuple<MDPState *, float, bool> Environment::step(int action) {
    // get distributions according to environment dynamics (current state and action chosen by agent)
    map<tuple<MDPState *, float>, float> distributions = p(curr_state, action);
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
    curr_state = get<0>(next_state_reward);
    // checking for terminal state
    bool done = curr_state->terminal;
    // returns: next_state (MDPState), reward (float), done (bool)
    tuple<MDPState *, float, bool> state_reward_bool = tuple_cat(next_state_reward, make_tuple(done));
    return state_reward_bool;
}

bool Environment::save(std::string outputFileName) {
    stringstream s;
    // Create root.
    TiXmlDocument doc;
    TiXmlElement *root = new TiXmlElement("Environment");
    doc.LinkEndChild(root);

    TiXmlElement *width_segment = new TiXmlElement("width");
    root->LinkEndChild(width_segment);
    s << width;
    TiXmlText *width_txt = new TiXmlText(s.str().c_str());
    width_segment->LinkEndChild(width_txt);
    s.str("");

    TiXmlElement *height_segment = new TiXmlElement("height");
    root->LinkEndChild(height_segment);
    s << height;
    TiXmlText *height_txt = new TiXmlText(s.str().c_str());
    height_segment->LinkEndChild(height_txt);
    s.str("");

    TiXmlElement *seed_segment = new TiXmlElement("seed");
    root->LinkEndChild(seed_segment);
    s << seed;
    TiXmlText *seed_txt = new TiXmlText(s.str().c_str());
    seed_segment->LinkEndChild(seed_txt);
    s.str("");

    TiXmlElement *deterministic_segment = new TiXmlElement("deterministic");
    root->LinkEndChild(deterministic_segment);
    s << deterministic;
    TiXmlText *deterministic_txt = new TiXmlText(s.str().c_str());
    deterministic_segment->LinkEndChild(deterministic_txt);
    s.str("");

    TiXmlElement *livingreward_segment = new TiXmlElement("livingreward");
    root->LinkEndChild(livingreward_segment);
    s << living_reward;
    TiXmlText *livingreward_txt = new TiXmlText(s.str().c_str());
    livingreward_segment->LinkEndChild(livingreward_txt);
    s.str("");

    TiXmlElement *endreward_segment = new TiXmlElement("endreward");
    root->LinkEndChild(endreward_segment);
    s << end_reward;
    TiXmlText *endreward_txt = new TiXmlText(s.str().c_str());
    endreward_segment->LinkEndChild(endreward_txt);
    s.str("");

    TiXmlElement *percentageobstacles_segment = new TiXmlElement("percentageobstacles");
    root->LinkEndChild(percentageobstacles_segment);
    s << percentage_obstacles;
    TiXmlText *percentageobstacles_txt = new TiXmlText(s.str().c_str());
    percentageobstacles_segment->LinkEndChild(percentageobstacles_txt);
    s.str("");

    doc.SaveFile(("data/" + outputFileName).c_str());
    return true;
}

void Environment::generate_non_deterministic_world() {
    Random random(seed);
    float obst_percentage = this->percentage_obstacles / 8.0;
    generate_non_deterministic_obstacles();
    generate_obstacles(obst_percentage);
    for (auto &current_state: states) {
        int x = current_state.x;
        int y = current_state.y;
        MDPState *next_state = get_state_by_coordinates(x, y + 1);
        // check bounds of environment -> if actions leads outside bounds, stay put
        if (y + 1 >= height || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
        } else {
            next_state = get_state_by_coordinates(x, y + 1);
        }
        if (next_state->symbol == "w") {
            int drifting_amount = random.rand() % 4;
            for (int i = 0; i < drifting_amount; i++) {
                int dx = ((random.rand() % 2) * 2) - 1;
                int dy = ((random.rand() % 2) * 2) - 1;
                MDPState *displacement_state = get_state_by_coordinates(x + dx, y + dy);
                if (displacement_state == nullptr) displacement_state = next_state;
                insert_non_deterministic_dynamics(&current_state, 0, living_reward,
                                                  (drifting_away_chance / (float) drifting_amount), displacement_state);
            }
            insert_non_deterministic_dynamics(&current_state, 0, living_reward, ((1 - drifting_away_chance) +
                                                                                 (drifting_away_chance /
                                                                                  (float) drifting_amount)),
                                              next_state);
        } else if (next_state->symbol == "L") {
            insert_non_deterministic_dynamics(&current_state, 0, lava_reward, 1, next_state);
        } else {
            insert_non_deterministic_dynamics(&current_state, 0, living_reward, 1, next_state);
        }
        next_state = get_state_by_coordinates(x, y - 1);
        if (y - 1 < 0 || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
        } else {
            next_state = get_state_by_coordinates(x, y - 1);
        }

        if (next_state->symbol == "w") {
            int drifting_amount = random.rand() % 4;
            for (int i = 0; i < drifting_amount; i++) {
                int dx = ((random.rand() % 2) * 2) - 1;
                int dy = ((random.rand() % 2) * 2) - 1;
                MDPState *displacement_state = get_state_by_coordinates(x + dx, y + dy);
                if (displacement_state == nullptr) displacement_state = next_state;
                insert_non_deterministic_dynamics(&current_state, 2, living_reward,
                                                  (drifting_away_chance / (float) drifting_amount), displacement_state);
            }
            insert_non_deterministic_dynamics(&current_state, 2, living_reward, ((1 - drifting_away_chance) +
                                                                                 (drifting_away_chance /
                                                                                  (float) drifting_amount)),
                                              next_state);
        } else if (next_state->symbol == "L") {
            insert_non_deterministic_dynamics(&current_state, 2, lava_reward, 1, next_state);
        } else {
            insert_non_deterministic_dynamics(&current_state, 2, living_reward, 1, next_state);
        }

        next_state = get_state_by_coordinates(x + 1, y);
        if (x + 1 >= width || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
        } else {
            next_state = get_state_by_coordinates(x + 1, y);
        }

        if (next_state->symbol == "w") {
            int drifting_amount = random.rand() % 4;
            for (int i = 0; i < drifting_amount; i++) {
                int dx = ((random.rand() % 2) * 2) - 1;
                int dy = ((random.rand() % 2) * 2) - 1;
                MDPState *displacement_state = get_state_by_coordinates(x + dx, y + dy);
                if (displacement_state == nullptr) displacement_state = next_state;
                insert_non_deterministic_dynamics(&current_state, 1, living_reward,
                                                  (drifting_away_chance / (float) drifting_amount), displacement_state);
            }
            insert_non_deterministic_dynamics(&current_state, 1, living_reward, ((1 - drifting_away_chance) +
                                                                                 (drifting_away_chance /
                                                                                  (float) drifting_amount)),
                                              next_state);
        } else if (next_state->symbol == "O") {
            insert_non_deterministic_dynamics(&current_state, 1, lava_reward, 1, next_state);
        } else {
            insert_non_deterministic_dynamics(&current_state, 1, living_reward, 1, next_state);
        }


        next_state = get_state_by_coordinates(x - 1, y);
        if (x - 1 < 0 || next_state->symbol == "O") {
            next_state = get_state_by_coordinates(x, y);
        } else {
            next_state = get_state_by_coordinates(x - 1, y);
        }
        if (next_state->symbol == "w") {
            int drifting_amount = random.rand() % 4;
            for (int i = 0; i < drifting_amount; i++) {
                int dx = ((random.rand() % 2) * 2) - 1;
                int dy = ((random.rand() % 2) * 2) - 1;
                MDPState *displacement_state = get_state_by_coordinates(x + dx, y + dy);
                if (displacement_state == nullptr) displacement_state = next_state;
                insert_non_deterministic_dynamics(&current_state, 3, living_reward,
                                                  (drifting_away_chance / (float) drifting_amount), displacement_state);
            }
            insert_non_deterministic_dynamics(&current_state, 3, living_reward, ((1 - drifting_away_chance) +
                                                                                 (drifting_away_chance /
                                                                                  (float) drifting_amount)),
                                              next_state);
        } else if (next_state->symbol == "L") {
            insert_non_deterministic_dynamics(&current_state, 3, lava_reward, 1, next_state);
        } else {
            insert_non_deterministic_dynamics(&current_state, 3, living_reward, 1, next_state);
        }
    }
}

void Environment::generate_non_deterministic_obstacles() {
    Random random(seed);
    std::vector<std::vector<char>> lava_map;
    std::vector<std::vector<char>> river_map;
    int index = -1;
    // generate lava_pools until the start and end are not lava-objects
    do {
        lava_map.clear();
        std::vector<char> tmp;
        tmp.resize(width, '-');
        lava_map.resize(height, tmp);
        index += 1;
        LavaPools::Lava(lava_map, random.rand() % 3, seed + index);
        // in the wile loop we have to check for sudden death
    } while (lava_map[start->y][start->x] != '-' and lava_map[end->y][end->x] != '-');

    index = -1;
    // generate rivers until the start and end are not river or bridge objects
    do {
        river_map.clear();
        std::vector<char> tmp;
        tmp.resize(width, '-');
        river_map.resize(height, tmp);
        index += 1;
        RiverBezier::River(river_map, random.rand() % 3, seed + index);
    } while (river_map[start->y][start->x] != '-' and river_map[end->y][end->x] != '-');

    // filling the environment with river and lavapits
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            MDPState *current_state = get_state_by_coordinates(x, y);
            if (current_state->symbol != "X" and current_state->symbol != "E") {
                if (lava_map[y][x] == 'L') {
                    current_state->symbol = 'L';
                }
                if (river_map[y][x] == 'w') current_state->symbol = 'w';
                if (river_map[y][x] == 'b') current_state->symbol = 'b';
            }
        }
    }
}

void
Environment::insert_non_deterministic_dynamics(MDPState *current_state, int action, float reward, float probability,
                                               MDPState *next_state) {
    if (next_state == end) {
        reward = end_reward;
    }
    tuple<MDPState *, float> next_state_reward(next_state, reward);
    tuple<MDPState *, int> current_state_action(current_state, action);

    dynamics[current_state_action].insert({next_state_reward, probability});
}

inline int manhattanLenght(MDPState u, MDPState v){
    return abs(u.x - v.x) + abs(u.y - v.y);
}

std::stack<MDPState> Environment::runDijkstra() {

    vector<tuple<int, int>> Q;
    std::map<tuple<int, int>, int> distanceMap;
    std::map<tuple<int, int>, tuple<int, int>> previousMap;

    bool possible = true;

    for(MDPState state : states){
        if(state.symbol != "O"){
            distanceMap[tuple(state.x, state.y)] = std::numeric_limits<int>::max();
            previousMap[tuple(state.x, state.y)];
            Q.push_back(make_tuple(state.x, state.y));
            if(state == *start){
                distanceMap[tuple(state.x, state.y)] = 0;
            }
        }
    }

    while(!Q.empty()){
        MDPState u;
        // Get vertex with minimum distance
        int smallestD = std::numeric_limits<int>::max();
        for(tuple<int, int> state : Q){
            if(distanceMap[state] < smallestD){
                u = *get_state_by_coordinates(get<0>(state), get<1>(state));
                smallestD = distanceMap[state];
            }
        }
        if(smallestD == std::numeric_limits<int>::max()){
            possible = false;
            break;
        }

        Q.erase(find(Q.begin(), Q.end(), make_tuple(u.x, u.y)));
        if(u == *end){
            break;
        }

        // Get all valid neighbors that are still in Q.
        vector<tuple<int, int>> friendlyNeighbors;
        if(u.x - 1 >= 0){
            for(tuple<int, int> state : Q){
                if(*get_state_by_coordinates(get<0>(state), get<1>(state)) == *get_state_by_coordinates(u.x - 1, u.y)){
                    friendlyNeighbors.push_back(make_tuple(u.x - 1, u.y));
                }
            }
        }
        if(u.x + 1 < width){
            for(tuple<int, int> state : Q){
                if(*get_state_by_coordinates(get<0>(state), get<1>(state)) == *get_state_by_coordinates(u.x + 1, u.y)){
                    friendlyNeighbors.push_back(make_tuple(u.x + 1, u.y));
                }
            }
        }
        if(u.y - 1 >= 0){
            for(tuple<int, int> state : Q){
                if(*get_state_by_coordinates(get<0>(state), get<1>(state)) == *get_state_by_coordinates(u.x, u.y - 1)){
                    friendlyNeighbors.push_back(make_tuple(u.x, u.y - 1));
                }
            }
        }
        if(u.y + 1 < height){
            for(tuple<int, int> state : Q){
                if(*get_state_by_coordinates(get<0>(state), get<1>(state)) == *get_state_by_coordinates(u.x, u.y + 1)){
                    friendlyNeighbors.push_back(make_tuple(u.x, u.y + 1));
                }
            }
        }
        for(tuple<int, int> v : friendlyNeighbors){
            int alt = distanceMap[tuple(u.x, u.y)] + manhattanLenght(u, *get_state_by_coordinates(get<0>(v), get<1>(v)));
            if(alt < distanceMap[v]){
                distanceMap[v] = alt;
                previousMap[v] = tuple(u.x, u.y);
            }
        }
    }
    if(possible){
        std::stack<MDPState> s;
        MDPState u = *end;
        while(!(u == *start)){
            s.push(u);
            std::tuple<int , int > temp = previousMap[tuple(u.x, u.y)];
            u = *get_state_by_coordinates(get<0>(temp), get<1>(temp));
        }
        s.push(u);
        return s;
    }
    else{
        return stack<MDPState>();
    }

}


