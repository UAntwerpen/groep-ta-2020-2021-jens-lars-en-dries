#include "datastructures/Environment.h"
#include "datastructures/LA.h"
#include "datastructures/Agent.h"
#include "parser/LAParser.h"

int main() {
    LA* parse_test = new LA();
    LAParser Q = LAParser();
    Q.loadFile("data/LAParserTest.xml");
//    Q.parseFile(parse_test);

    std::vector<int> actions{0, 1, 2, 3};
//    parse_test->save();

    Environment env = Environment(10, 10, 42, true, -0.01, 10, 0.2);
    LA la(10, 10, std::make_pair(env.start->x, env.start->y), actions);
    la.save("beepboop.xml");
    Q.loadFile("data/beepboop.xml");
    Q.parseFile(parse_test);
    Agent agent(*parse_test, 0.01);
    env.render();

    agent.learn(1000, env);
    env.reset();

    std::cout<<"Finished learning.\n";

    double average=0;
    for(int i=0;i<50;i++){
        env.reset();
        average+=agent.play(env).size();
    }

    std::cout<<"Average steps random = "<<average/(double)50<<std::endl;

    average=0;
    for(int i=0;i<50;i++){
        env.reset();
        average+=agent.play(env).size();
    }

    std::cout<<"Average steps = "<<average/(double)50<<std::endl;

    std::cout<<"Optimal route size = "<<agent.getOptimalRoute(env).size()<<std::endl;

    return 0;
}