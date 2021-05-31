#ifndef TO_GROEP_ABSTRACTAGENT_H
#define TO_GROEP_ABSTRACTAGENT_H


#include <datastructures/Environment.h>
#include <datastructures/State.h>
#include <datastructures/LA.h>

class AbstractAgent {
public:
    virtual void train(Environment& gridworld, int nr_episodes, int max_steps, int prints_every_epoch) = 0;
    virtual std::vector<std::tuple<State*, int, float >> play(Environment& gridworld, int max_steps) = 0;

    virtual void save(string outfileName) = 0;
    virtual void load(LA* savedLA) = 0;

    virtual float score(Environment& gridworld, LA* la);


};


#endif //TO_GROEP_ABSTRACTAGENT_H
