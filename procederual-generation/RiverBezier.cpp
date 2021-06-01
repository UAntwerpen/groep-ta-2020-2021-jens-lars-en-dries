//
// Created by syntaxnoob on 4/3/21.
//

#include <cmath>
#include "RiverBezier.h"

Point Point::operator+(Point &other_point) const {
    return {x + other_point.getX(), y + other_point.getY()};
}

Point Point::operator*(const Point &in_point) const {
    return {x * in_point.getX(), y * in_point.getY()};
}

void RiverBezier::River(std::vector<std::vector<char>> &map, int bridge_amount, int seed) {
    // generate random source
    Random random;
    if (seed != -1) random.setSeed(seed);
    // calculate height and width
    int height = map.size();
    int width = map[0].size();

    // generate control points and push back into control points vector.
    std::vector<Point> control_points;

    Point p0(0, random.rand() % (height - 2) + 1);
    Point p1(random.rand() % (width - 2) + 1, 0);
    Point p2(width, random.rand() % (height - 2) + 1);
    Point p3(random.rand() % (width - 2) + 1, height);

    control_points.push_back(p0);
    control_points.push_back(p1);
    control_points.push_back(p2);
    control_points.push_back(p3);

    // calculate the order of control points for line generation
    int random_start = random.rand() % 4;
    int first_id{random_start}, second_id, third_id, fourth_id;
    if (random_start % 2 == 0) {
        second_id = (random_start + 1) % 4;
        third_id = (random_start + 2) % 4;
        fourth_id = (random_start + 3) % 4;
    } else {
        second_id = (random_start + 1) % 4;
        third_id = (random_start + 3) % 4;
        fourth_id = (random_start + 2) % 4;
    }
    //calculate precision
    int presision = height * width;
    // plot presision points for high resolution bezier curve
    for (int i{0}; i < presision; i++) {
        double x_result, y_result, t;
        // generate bridge elements
        if (bridge_amount != 0 and i % (presision / bridge_amount) == (presision / (bridge_amount * 2))) {
            // generate presision/30 bridge elements
            for (int j = 0; j < presision / 30; j++) {
                t = (double) (i + j) / presision;
                x_result = (std::pow(1 - t, 3) * control_points[first_id].getX()) +
                           (3 * std::pow(1 - t, 2) * (t) * control_points[second_id].getX()) +
                           (3 * std::pow((t), 2) * (1 - t) * control_points[third_id].getX()) +
                           (std::pow(t, 3) * control_points[fourth_id].getX());
                y_result = std::pow(1 - t, 3) * control_points[first_id].getY() +
                           (3 * std::pow(1 - t, 2) * (t) * control_points[second_id].getY()) +
                           (3 * std::pow(t, 2) * (1 - t) * control_points[third_id].getY()) +
                           (std::pow(t, 3) * control_points[fourth_id].getY());
                Point a(std::round(x_result), std::round(y_result));
                x_result = (std::pow(1 - t, 3) * control_points[first_id].getX()) +
                           (3 * std::pow(1 - t, 2) * t * control_points[second_id].getX() + 1) +
                           (3 * std::pow(t, 2) * (1 - t) * control_points[third_id].getX()) +
                           (std::pow(t, 3) * control_points[fourth_id].getX());
                y_result = std::pow(1 - t, 3) * control_points[first_id].getY() +
                           (3 * std::pow(1 - t, 2) * t * control_points[second_id].getY() + 0.5) +
                           (3 * std::pow(t, 2) * (1 - t) * control_points[third_id].getY()) +
                           (std::pow(t, 3) * control_points[fourth_id].getY());
                Point b(std::round(x_result), std::round(y_result));
                if (a.getX() < width and a.getY() < height) map[a.getY()][a.getX()] = 'b'; // b stand for bridge
                if (b.getX() < width and b.getY() < height) map[b.getY()][b.getX()] = 'b'; // b stand for bridge
            }
        }
            // generate water elements
        else {
            t = (double) i / presision;
            // calculate x and y value of points
            x_result = (std::pow(1 - t, 3) * control_points[first_id].getX()) +
                       (3 * std::pow(1 - t, 2) * t * control_points[second_id].getX()) +
                       (3 * std::pow(t, 2) * (1 - t) * control_points[third_id].getX()) +
                       (std::pow(t, 3) * control_points[fourth_id].getX());
            y_result = std::pow(1 - t, 3) * control_points[first_id].getY() +
                       (3 * std::pow(1 - t, 2) * t * control_points[second_id].getY()) +
                       (3 * std::pow(t, 2) * (1 - t) * control_points[third_id].getY()) +
                       (std::pow(t, 3) * control_points[fourth_id].getY());
            Point a(std::round(x_result), std::round(y_result));
            // calculate new x value with the 2nd control point moved by 1 x value(impossible to be out of bounds).
            x_result = (std::pow(1 - t, 3) * control_points[first_id].getX()) +
                       (3 * std::pow(1 - t, 2) * t * control_points[second_id].getX() + 1) +
                       (3 * std::pow(t, 2) * (1 - t) * control_points[third_id].getX()) +
                       (std::pow(t, 3) * control_points[fourth_id].getX());
            y_result = std::pow(1 - t, 3) * control_points[first_id].getY() +
                       (3 * std::pow(1 - t, 2) * t * control_points[second_id].getY() + 0.5) +
                       (3 * std::pow(t, 2) * (1 - t) * control_points[third_id].getY()) +
                       (std::pow(t, 3) * control_points[fourth_id].getY());
            Point b(std::round(x_result), std::round(y_result));

            if (a.getX() < width and a.getY() < height and map[a.getY()][a.getX()] != 'b') {
                map[a.getY()][a.getX()] = 'w'; // w stand for water obstacle
            }
            if (b.getX() < width and b.getY() < height and map[b.getY()][b.getX()] != 'b') {
                map[b.getY()][b.getX()] = 'w'; // w stand for water obstacle
            }
        }
    }
}
