#ifndef TO_GROEP_ENVIRONMENTPARSER_H
#define TO_GROEP_ENVIRONMENTPARSER_H


#include "AbstractParser.h"
#include "../datastructures/Environment.h"

class EnvironmentParser : public AbstractParser {
public:
    /*
     * Function handles the parsing of an Environment. All the data gets added to the Environment object provided by user.
     * @return Environment* Pointer to object of type Environment which is created with the data in inputfile.
     */
    Environment* parseFile();
private:
    int fWidth;
    int fHeight;
    int fSeed;
    bool fDeterministic;
    float fLivingReward;
    float fEndReward;
    float fPercentageObstacles;
};


#endif //TO_GROEP_ENVIRONMENTPARSER_H
