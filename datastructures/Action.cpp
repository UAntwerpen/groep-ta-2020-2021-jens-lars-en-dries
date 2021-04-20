//
// Created by driesdemaeseneer on 4/17/21.
//

#include "Action.h"
#include "State.h"

bool Action::operator==(Action& action) {
    for(auto i:chance_per_transition){
        bool found = false;
        for(auto j:action.chance_per_transition){
            if(i.first==j.first and i.second ==j.second){
                found = true;
            }
        }
        if(!found) return false;
    }
    return true;
}
