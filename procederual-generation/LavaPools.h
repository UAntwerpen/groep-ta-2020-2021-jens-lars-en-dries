//
// Created by syntaxnoob on 5/7/21.
//

#ifndef PROCEDURAL_GENERATOR_LAVAPOOLS_H
#define PROCEDURAL_GENERATOR_LAVAPOOLS_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "../random/Random.h"

class LavaPools {
public:
    static void Lava(std::vector<std::vector<char>>& map, int lava_pits, int seed = -1);
};


#endif //PROCEDURAL_GENERATOR_LAVAPOOLS_H