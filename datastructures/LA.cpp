//
// Created by driesdemaeseneer on 4/15/21.
//

#include <tuple>
#include "LA.h"

void LA::reset() {

}

State *LA::G(State *in_state, int in_action) {
    for(auto& it: in_state->getActionToState()){
        if(it.first == in_action) return it.second;
    }
    return in_state;
}

int LA::pickAction(State *in_state) {
    int current_max = std::numeric_limits<int>::min();
    int current_action;
    for(auto it: in_state->getValue1()){
        if(it.second<current_max){
            current_action = it.first;
        }
    }
    return current_action;
}

State *LA::coordinatesToState(std::tuple<int, int> in_coords) {
    for (auto it: coordinates_to_state) {
        if (std::make_tuple(it.first.first, it.first.second) == in_coords) return it.second;
    }
}
