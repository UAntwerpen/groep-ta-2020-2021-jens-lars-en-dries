//
// Created by syntaxnoob on 4/20/21.
//

#ifndef TO_GROEP_RANDOM_H
#define TO_GROEP_RANDOM_H

#include <ctime>
#include <vector>

class Random {
    double seed;
public:
    // constructors
    Random(int in_seed): seed(in_seed){}
    Random();

    //random integer
    int random();
    int rand(){return random();}

    //random item in range
    int rand(int input1, int input2) {return random_range(input1, input2);}
    int random_range(int input1, int input2);

    // set seed
    void setSeed(int in_seed){seed = in_seed;}

    //random element in vector of anny type with equal probability
    template<typename T>
    T random_item(std::vector<T> input_vector){ return input_vector[rand(0, input_vector.size()-1)]; }

};


#endif //TO_GROEP_RANDOM_H
