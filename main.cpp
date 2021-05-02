#include "datastructures/Environment.h"
#include "datastructures/LA.h"
#include "datastructures/Agent.h"
#include "parser/LAParser.h"

int main() {
    LA* parse_test = new LA();
//    LAParser Q = LAParser();

    std::vector<int> actions{0, 1, 2, 3};

    Environment env = Environment(20, 20, 9, true, -0.01, 10, 0.2);
    LA la(20, 20, std::make_pair(env.start->x, env.start->y), actions);
    Agent agent(la, 0.1);
    env.render();

    agent.learn(10000, env);
    env.reset();

    std::cout<<"Finished learning.\n";
    // Save the LA
//    la.save("beepboop.xml");
    // Load savefile into Parser, then parse file.
//    Q.loadFile("data/beepboop.xml");
//    Q.parseFile(parse_test);
    // Result should be that both parse_test and

    double average=0;
    for(int i=0;i<100;i++){
        env.reset();
        average+=agent.play(env).size();
    }

    std::cout<<"Average steps random = "<<average/(double)100<<std::endl;

    average=0;
    for(int i=0;i<100;i++){
        env.reset();
        average+=agent.play(env).size();
    }

    std::cout<<"Average steps = "<<average/(double)100<<std::endl;

    std::cout<<"Optimal route size = "<<agent.getOptimalRoute(env).size()<<std::endl;

    return 0;
}