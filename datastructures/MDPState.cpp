#include "MDPState.h"

MDPState::MDPState(int x, int y, string symbol, bool terminal) {
    this->x = x;
    this->y = y;
    this->symbol = symbol;
    this->terminal = terminal;
}