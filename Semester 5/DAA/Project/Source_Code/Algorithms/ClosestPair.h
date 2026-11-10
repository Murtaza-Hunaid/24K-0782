#ifndef CLOSESTPAIR_H
#define CLOSESTPAIR_H

#include <vector>

struct Point {
    double x;
    double y;
};

struct ClosestPairResult {
    Point first;
    Point second;
    double distance;
};

// Finds the closest pair of points using Divide and Conquer.
ClosestPairResult closestPair(const std::vector<Point>& points);

#endif