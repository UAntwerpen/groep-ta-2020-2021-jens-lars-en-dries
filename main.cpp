#include "datastructures/Environment.h"
#include "datastructures/LA.h"
#include "datastructures/Agent.h"

int main() {
    std::vector<int> actions{0, 1, 2, 3};

    Environment env = Environment(5, 5, 42, true, -0.01, 10, 0.2);
    LA la(5, 5, std::make_pair(env.start->x, env.start->y), actions);
    Agent agent(la, 0.1);
    env.render();

    agent.learn(1000, env);
    env.reset();

    std::cout<<"Finished learning.\n";

    double average=0;
    for(int i=0;i<50;i++){
        env.reset();
        average+=agent.play(env).size();
    }

    std::cout<<"Average steps = "<<average/(double)50<<std::endl;

    std::cout<<"Optimal route size = "<<agent.getOptimalRoute(env).size()<<std::endl;

    return 0;
}