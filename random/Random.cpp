//
// Created by driesdemaeseneer on 4/20/21.
//

#include <complex>
#include "Random.h"
#include <limits>
#include <iostream>

int Random::random() {
    // Linear congruential generator with "Numerical Recipes"  parameters
    seed = std::remainder((1664525 * seed + 1013904223),std::pow(2,32));
    return std::abs(std::remainder(seed, std::numeric_limits<int>::max()));
}

Random::Random() {
    seed = time(nullptr);
}

int Random::random_range(int input1, int input2) {
    if(input1 > input2) std::swap(input1, input2);
    return std::abs(std::round(input1 + (input2-input1)*((double)(rand()%1001)/1000.0)));
}

