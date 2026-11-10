#include "../Algorithms/ClosestPair.h"
#include "../Algorithms/Karatsuba.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cout << "========== ALGORITHM TESTS ==========\n\n";

    // Test 1: Closest Pair
    cout << "Test 1: Closest Pair\n";

    vector<Point> points = {
        {0, 0},
        {5, 5},
        {1, 1},
        {10, 10},
        {20, 20}
    };

    ClosestPairResult result = closestPair(points);

    cout << "Closest points: ("
         << result.first.x << ", " << result.first.y
         << ") and ("
         << result.second.x << ", " << result.second.y
         << ")\n";

    cout << "Distance: " << result.distance << '\n';

    if (abs(result.distance - sqrt(2.0)) < 1e-9) {
        cout << "PASS\n\n";
    } else {
        cout << "FAIL\n\n";
    }

    // Test 2: Duplicate points
    cout << "Test 2: Duplicate Points\n";

    vector<Point> duplicatePoints = {
        {2, 3},
        {5, 6},
        {2, 3},
        {10, 10}
    };

    ClosestPairResult duplicateResult =
        closestPair(duplicatePoints);

    cout << "Distance: " << duplicateResult.distance << '\n';

    if (duplicateResult.distance == 0.0) {
        cout << "PASS\n\n";
    } else {
        cout << "FAIL\n\n";
    }

    // Test 3: Karatsuba small multiplication
    cout << "Test 3: Karatsuba Small Multiplication\n";

    string product = multiplyKaratsuba("123", "456");

    cout << "123 x 456 = " << product << '\n';

    if (product == "56088") {
        cout << "PASS\n\n";
    } else {
        cout << "FAIL\n\n";
    }

    // Test 4: Karatsuba multiplication with zeros
    cout << "Test 4: Karatsuba Zero Multiplication\n";

    product = multiplyKaratsuba("123456789", "0");

    cout << "Result: " << product << '\n';

    if (product == "0") {
        cout << "PASS\n\n";
    } else {
        cout << "FAIL\n\n";
    }

    // Test 5: Karatsuba with leading zeros
    cout << "Test 5: Leading Zeros\n";

    product = multiplyKaratsuba("0000123", "00456");

    cout << "Result: " << product << '\n';

    if (product == "56088") {
        cout << "PASS\n\n";
    } else {
        cout << "FAIL\n\n";
    }

    cout << "========== TESTS COMPLETED ==========\n";

    return 0;
}