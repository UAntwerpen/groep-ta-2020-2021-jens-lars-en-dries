//
// Created by driesdemaeseneer on 4/15/21.
//

#include "State.h"

State *State::operator[](Action action) const {
    for(auto it:action_to_state){
        if(it.first == action){
            return it.second;
        }
    }
    return nullptr;
}

double State::operator[](State *state) const {
    for(auto& it:state_to_probability){
        if(&it.first == &state){
            return it.second;
        }
    }
    return 0;
}
