#include "MDPState.h"

MDPState::MDPState(int x, int y, string type, bool terminal) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->terminal = terminal;
}