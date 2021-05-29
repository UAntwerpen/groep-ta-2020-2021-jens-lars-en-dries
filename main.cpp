#include "datastructures/Environment.h"
#include "datastructures/LA.h"
#include "algorithms/MCLearning.h"
#include "parser/LAParser.h"
#include "parser/EnvironmentParser.h"
#include "visualisatie/mainwindow.h"
#include <stack>

#include <QApplication>

int main(int argc, char *argv[]) {
    LA* parse_test = new LA();
    LAParser Q = LAParser();

    std::vector<int> actions{0, 1, 2, 3};

    // 0.22 lukt prima 0.23 precies niet.
    Environment env = Environment(20, 20, 3, true, -0.01, 10, 0.2);
    MCLearning agent(env, 0.1);
    env.render();
//    agent.train(env, 1000, 200, 200);
//    env.reset();
    agent.save("../tests/testData/savedLA.xml");

    double average=0;
    for(int i=0;i<50;i++){
        env.reset();
        average+=agent.play(env, 200).size();
    }

//    agent.train(env, 1000, 200, 100);
//    env.reset();

    std::cout<<"Finished learning.\n";
    // Save the LA

    // Load savefile into Parser, then parse file.
//    Q.loadFile("data/testLA.xml");
//    Q.parseFile(parse_test);
    // Result should be that both parse_test and la are identical
    std::cout<<"Average steps random = "<<average/(double)50<<std::endl;

    // Save the environment.
    env.save("testEnv.xml");
//     Create EnvironmentParser, load inputfile, parseFile returns a pointer to Environment.
    EnvironmentParser W;
    W.loadFile("data/testEnv.xml");
    Environment* loadENVTest = W.parseFile();
    average=0;
    for(int i=0;i<50;i++){
        env.reset();
        average+=agent.play(env, 200).size();
    }

    std::cout<<"Average steps = "<<average/(double)50<<std::endl;

    // Aantal vakken van start -> einde, inclusief de start en eindvakken.
    auto stackpath = env.runDijkstra();
    std::cout << "Optimal route size = " <<stackpath.size() << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}