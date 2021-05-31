#include "AbstractAgent.h"

float AbstractAgent::score(Environment &gridworld, LA *la) {
    LA deterministic_automaton = la->toDeterministic();
    std::pair<int,int> current_coordinates = std::make_pair(gridworld.start->x, gridworld.start->y);
    unsigned int step_count = 0;
    gridworld.reset();

    while(current_coordinates != std::make_pair(gridworld.end->x, gridworld.end->y) and step_count<300) {

        State* next_state = deterministic_automaton.coordinatesToState(current_coordinates);
        current_coordinates = deterministic_automaton.G(next_state,deterministic_automaton.pickAction(next_state))->getCoordinates();

        step_count++;
    }
    return (float)gridworld.runDijkstra().size()/(float)step_count;
}
