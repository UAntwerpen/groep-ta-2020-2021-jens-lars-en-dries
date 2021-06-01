//
// Created by syntaxnoob on 4/3/21.
//

#ifndef PROCEDURAL_GENERATOR_RIVERBEZIER_H
#define PROCEDURAL_GENERATOR_RIVERBEZIER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include "../random/Random.h"

class Point {
    int x{}, y{};
public:
    Point() = default;

    Point(int in_x, int in_y) : x(in_x), y(in_y) {}

    int getX() const { return x; }

    int getY() const { return y; }

    template<typename T>
    void operator*(const T &scalar) {
        x = std::round(x * scalar);
        y = std::round(y * scalar);
    }

    Point operator*(const Point &in_point) const;

    Point operator+(Point &other_point) const;

};

class RiverBezier {
public:
    static void River(std::vector<std::vector<char>> &map, int bridge_amount, int seed = -1);
};


#endif //PROCEDURAL_GENERATOR_RIVERBEZIER_H
