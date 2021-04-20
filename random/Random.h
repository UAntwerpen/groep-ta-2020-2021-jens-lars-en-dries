//
// Created by syntaxnoob on 4/20/21.
//

#ifndef TO_GROEP_RANDOM_H
#define TO_GROEP_RANDOM_H


class Random {
    double seed;
public:
    Random(int in_seed): seed(in_seed){}
    double random();

};


#endif //TO_GROEP_RANDOM_H
