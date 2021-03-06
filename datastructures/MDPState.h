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
    MDPState() = default;
    MDPState(int x, int y, string symbol, bool terminal);
    bool operator== (const MDPState &c1)
    {
        return (c1.x == x &&
                c1.y == y);
    }
    bool operator< (const MDPState& c1) const { return (c1.x < x); }

};


#endif //TO_GROEP_MDPSTATE_H
