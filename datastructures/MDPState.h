#ifndef TO_GROEP_MDPSTATE_H
#define TO_GROEP_MDPSTATE_H
#include <string>

using namespace std;

class MDPState {
public:
    int x;
    int y;
    string symbol;
    bool terminal;
    MDPState(int x, int y, string symbol, bool terminal);
};


#endif //TO_GROEP_MDPSTATE_H
