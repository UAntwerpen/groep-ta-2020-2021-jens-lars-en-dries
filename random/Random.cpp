//
// Created by driesdemaeseneer on 4/20/21.
//

#include <complex>
#include "Random.h"

double Random::random() {
    // Linear congruential generator with "Numerical Recipes"  parameters
    seed = std::remainder((1664525 * seed + 1013904223),std::pow(2,32));
    return seed;
}
