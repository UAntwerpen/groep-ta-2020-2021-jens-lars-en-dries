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
    Environment parseFile();
private:
    int fWidth = 1;
    int fHeight = 1;
    int fSeed = 1;
    bool fDeterministic = 1;
    float fLivingReward = 1;
    float fEndReward = 1;
    float fPercentageObstacles = 1;
};


#endif //TO_GROEP_ENVIRONMENTPARSER_H
