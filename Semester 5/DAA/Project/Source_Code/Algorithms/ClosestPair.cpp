#include "ClosestPair.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

namespace {

struct IndexedPoint {
    Point point;
    int id;
};

struct InternalResult {
    int firstId = -1;
    int secondId = -1;
    double distanceSquared = numeric_limits<double>::infinity();
};

double squaredDistance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return dx * dx + dy * dy;
}

InternalResult bruteForce(
    const vector<IndexedPoint>& points,
    int left,
    int right
) {
    InternalResult result;

    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            double distance = squaredDistance(
                points[i].point,
                points[j].point
            );

            if (distance < result.distanceSquared) {
                result.distanceSquared = distance;
                result.firstId = points[i].id;
                result.secondId = points[j].id;
            }
        }
    }

    return result;
}

InternalResult solve(
    const vector<IndexedPoint>& pointsByX,
    const vector<IndexedPoint>& pointsByY,
    int left,
    int right
) {
    int count = right - left;

    // Base case: at most three points.
    if (count <= 3) {
        return bruteForce(pointsByX, left, right);
    }

    int mid = left + count / 2;
    double dividingX = pointsByX[mid].point.x;

    vector<IndexedPoint> leftY;
    vector<IndexedPoint> rightY;

    leftY.reserve(mid - left);
    rightY.reserve(right - mid);

    // Partition the y-sorted points into the two halves.
    for (const auto& p : pointsByY) {
        if (p.id < mid) {
            leftY.push_back(p);
        } else {
            rightY.push_back(p);
        }
    }

    InternalResult leftResult = solve(
        pointsByX, leftY, left, mid
    );

    InternalResult rightResult = solve(
        pointsByX, rightY, mid, right
    );

    InternalResult best =
        (leftResult.distanceSquared <= rightResult.distanceSquared)
        ? leftResult
        : rightResult;

    // Build the strip around the dividing line.
    vector<IndexedPoint> strip;
    strip.reserve(pointsByY.size());

    for (const auto& p : pointsByY) {
        double dx = p.point.x - dividingX;

        if (dx * dx < best.distanceSquared) {
            strip.push_back(p);
        }
    }

    // The strip is already sorted by y.
    // Check at most the next seven points.
    for (size_t i = 0; i < strip.size(); ++i) {
        for (
            size_t j = i + 1;
            j < strip.size() && j <= i + 7;
            ++j
        ) {
            double dy = strip[j].point.y - strip[i].point.y;

            if (dy * dy >= best.distanceSquared) {
                break;
            }

            double distance = squaredDistance(
                strip[i].point,
                strip[j].point
            );

            if (distance < best.distanceSquared) {
                best.distanceSquared = distance;
                best.firstId = strip[i].id;
                best.secondId = strip[j].id;
            }
        }
    }

    return best;
}

} 

ClosestPairResult closestPair(const vector<Point>& input) {
    if (input.size() < 2) {
        throw invalid_argument(
            "At least two points are required."
        );
    }

    vector<IndexedPoint> pointsByX;
    pointsByX.reserve(input.size());

    for (size_t i = 0; i < input.size(); ++i) {
        if (!isfinite(input[i].x) || !isfinite(input[i].y)) {
            throw invalid_argument(
                "Point coordinates must be finite."
            );
        }

        pointsByX.push_back({
            input[i],
            static_cast<int>(i)
        });
    }

    // Sort points by x-coordinate.
    sort(
        pointsByX.begin(),
        pointsByX.end(),
        [](const IndexedPoint& a, const IndexedPoint& b) {
            if (a.point.x != b.point.x) {
                return a.point.x < b.point.x;
            }

            if (a.point.y != b.point.y) {
                return a.point.y < b.point.y;
            }

            return a.id < b.id;
        }
    );

    // Assign IDs according to their positions in x-sorted order.
    for (size_t i = 0; i < pointsByX.size(); ++i) {
        pointsByX[i].id = static_cast<int>(i);
    }

    vector<IndexedPoint> pointsByY = pointsByX;

    // Sort points by y-coordinate.
    sort(
        pointsByY.begin(),
        pointsByY.end(),
        [](const IndexedPoint& a, const IndexedPoint& b) {
            if (a.point.y != b.point.y) {
                return a.point.y < b.point.y;
            }

            if (a.point.x != b.point.x) {
                return a.point.x < b.point.x;
            }

            return a.id < b.id;
        }
    );

    InternalResult result = solve(
        pointsByX,
        pointsByY,
        0,
        static_cast<int>(pointsByX.size())
    );

    return {
        pointsByX[result.firstId].point,
        pointsByX[result.secondId].point,
        sqrt(result.distanceSquared)
    };
}