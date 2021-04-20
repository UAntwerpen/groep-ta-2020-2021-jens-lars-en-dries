//
// Created by syntaxnoob on 4/20/21.
//

#ifndef TO_GROEP_RANDOM_H
#define TO_GROEP_RANDOM_H

#include <ctime>

class Random {
    double seed;
public:
    // constructor
    Random(int in_seed): seed(in_seed){}
    Random();
    int random();
    int rand(){return random();}
    void setSeed(int in_seed){seed = in_seed;}

};


#endif //TO_GROEP_RANDOM_H
