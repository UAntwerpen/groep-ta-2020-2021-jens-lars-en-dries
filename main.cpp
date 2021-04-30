#include "datastructures/Environment.h"

int main() {
    Environment env = Environment(5, 5, 42, true, -0.01, 10, 0.2);
    env.render();
    env.step(3);
    cout << "\n";
    env.render();
    env.step(0);
    cout << "\n";
    env.render();
    env.step(3);
    cout << "\n";
    env.render();
    env.step(3);
    cout << "\n";
    env.render();
    env.step(2);
    cout << "\n";
    env.render();
    env.step(2);
    cout << "\n";
    env.render();
    env.step(2);
    cout << "\n";
    env.render();
    env.step(3);
    cout << "\n";
    env.render();

    return 0;
}
