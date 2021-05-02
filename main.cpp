#include "datastructures/Environment.h"
#include "datastructures/LA.h"
#include "datastructures/Agent.h"

int main() {
    std::vector<int> actions{0, 1, 2, 3};

    Environment env = Environment(13, 11, 57, true, -0.025, 10, 0.2);
    LA la(13, 11, std::make_pair(env.start->x, env.start->y), actions);
    Agent agent(la, 0.2);
    env.render();

    agent.learn(100000, env);
    env.reset();

    std::cout<<"Finished learning.\n";

    double average=0;
    for(int i=0;i<100;i++){
        env.reset();
        average+=agent.play(env).size();
    }

    std::cout<<"Average steps = "<<average/(double)100<<std::endl;

    std::cout<<"Optimal route size = "<<agent.getOptimalRoute(env).size()<<std::endl;

    return 0;
}