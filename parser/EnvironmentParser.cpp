#include "EnvironmentParser.h"

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
    fLivingReward = stof(getRoot()->FirstChildElement("livingreward")->FirstChild()->ToText()->Value());
    fEndReward = stof(getRoot()->FirstChildElement("endreward")->FirstChild()->ToText()->Value());
    fPercentageObstacles = stof(getRoot()->FirstChildElement("percentageobstacles")->FirstChild()->ToText()->Value());

    Environment* returnENV = new Environment(fWidth, fHeight, fSeed, fDeterministic, fLivingReward, fEndReward, fPercentageObstacles);
    return returnENV;
}
