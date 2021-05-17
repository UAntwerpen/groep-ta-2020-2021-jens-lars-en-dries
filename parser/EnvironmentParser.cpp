#include "EnvironmentParser.h"
#include <sstream>

Environment* EnvironmentParser::parseFile() {
    fWidth = stoi(getRoot()->FirstChildElement("width")->FirstChild()->ToText()->Value());
    fHeight = stoi(getRoot()->FirstChildElement("height")->FirstChild()->ToText()->Value());
    fSeed = stoi(getRoot()->FirstChildElement("seed")->FirstChild()->ToText()->Value());
    if(stoi(getRoot()->FirstChildElement("deterministic")->FirstChild()->ToText()->Value()) == 1){
        fDeterministic = true;
    }
    else{
        fDeterministic = false;
    }
    // Dit werd eerst ook gedaan als hierboven maar dan met stof(), maar deze code bleek niet altijd correct te werken op mijn hardware.
    // Maar wel op de hardware van de andere, het aanmaken van nieuwe stringstreams per attribuut is essentieel om het op mijn hardware consistent te
    // laten werken.
    std::stringstream s;
    s << getRoot()->FirstChildElement("livingreward")->FirstChild()->ToText()->Value();
    s >> fLivingReward;
    std::stringstream x;
    x << getRoot()->FirstChildElement("endreward")->FirstChild()->ToText()->Value();
    x >> fEndReward;
    std::stringstream q;
    q << getRoot()->FirstChildElement("percentageobstacles")->FirstChild()->ToText()->Value();
    q >> fPercentageObstacles;
    Environment* returnENV = new Environment(fWidth, fHeight, fSeed, fDeterministic, fLivingReward, fEndReward, fPercentageObstacles);
    return returnENV;
}
