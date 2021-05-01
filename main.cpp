#include "datastructures/Environment.h"
#include "datastructures/LA.h"
#include "datastructures/Agent.h"

int main() {
    std::vector<int> actions{0, 1, 2, 3};

    Environment env = Environment(10, 10, 42, true, -0.1, 1, 0.2);
    LA la(16, 16, std::make_pair(env.start->x, env.start->y), actions);
    Agent agent(la, 0.1);

    env.render();

    auto tmp = agent.play(env);
    env.reset();

    agent.learn(100000, env);
    env.reset();
    agent.setEpsilon(0);
    auto tmp2 = agent.play(env);

    std::cout<<tmp.size()<<"  -  "<<tmp2.size()<<std::endl;

    return 0;
}