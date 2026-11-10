#include "../Algorithms/ClosestPair.h"
#include "../Algorithms/Karatsuba.h"

#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
namespace fs = std::filesystem;
using Clock = chrono::high_resolution_clock;

double bruteForceClosestPair(const vector<Point>& points) {
    double best = numeric_limits<double>::infinity();

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;

            best = min(best, dx * dx + dy * dy);
        }
    }

    return sqrt(best);
}

string schoolbookMultiply(const string& a, const string& b) {
    vector<int> digits(a.size() + b.size(), 0);

    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
        for (int j = static_cast<int>(b.size()) - 1; j >= 0; --j) {
            digits[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }

    for (int i = static_cast<int>(digits.size()) - 1; i > 0; --i) {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    string result;

    for (int digit : digits) {
        result += char('0' + digit);
    }

    size_t first = result.find_first_not_of('0');

    return first == string::npos ? "0" : result.substr(first);
}

void saveResult(
    const string& algorithm,
    const string& dataset,
    size_t inputSize,
    double timeMs,
    const string& result
) {
    fs::create_directories("results");

    const string filename = "results/benchmark.csv";
    bool needsHeader = !fs::exists(filename) ||
                       fs::file_size(filename) == 0;

    ofstream out(filename, ios::app);

    if (!out) {
        throw runtime_error("Could not open benchmark.csv");
    }

    if (needsHeader) {
        out << "Algorithm,Dataset,InputSize,TimeMs,Result\n";
    }

    out << algorithm << ','
        << dataset << ','
        << inputSize << ','
        << fixed << setprecision(3) << timeMs << ','
        << '"' << result << '"' << '\n';
}

void runClosestPair(const string& filename) {
    ifstream in(filename);

    if (!in) {
        throw runtime_error("Could not open dataset: " + filename);
    }

    size_t n;
    in >> n;

    vector<Point> points(n);

    for (auto& p : points) {
        if (!(in >> p.x >> p.y)) {
            throw runtime_error("Invalid closest-pair dataset.");
        }
    }

    cout << "Dataset: " << filename << '\n';
    cout << "Number of points: " << n << '\n';

    auto start = Clock::now();

    ClosestPairResult result = closestPair(points);

    auto end = Clock::now();

    double timeMs =
        chrono::duration<double, milli>(end - start).count();

    cout << fixed << setprecision(6);
    cout << "Closest distance: " << result.distance << '\n';
    cout << "First point: (" << result.first.x
         << ", " << result.first.y << ")\n";
    cout << "Second point: (" << result.second.x
         << ", " << result.second.y << ")\n";

    cout << "Execution time: " << timeMs << " ms\n";

    // Verify the answer against brute force for small datasets.
    if (n <= 5000) {
        double expected = bruteForceClosestPair(points);

        bool correct = abs(expected - result.distance) < 1e-9;

        cout << "Correctness: "
             << (correct ? "PASS" : "FAIL") << '\n';

        if (!correct) {
            throw runtime_error("Closest-pair correctness check failed.");
        }
    } else {
        cout << "Correctness: Not independently checked "
             << "(dataset too large for brute force).\n";
    }

    saveResult(
        "ClosestPair",
        fs::path(filename).filename().string(),
        n,
        timeMs,
        to_string(result.distance)
    );
}

void runMultiplication(const string& filename) {
    ifstream in(filename);

    if (!in) {
        throw runtime_error("Could not open dataset: " + filename);
    }

    string first, second;

    if (!(in >> first >> second)) {
        throw runtime_error("Invalid multiplication dataset.");
    }

    cout << "Dataset: " << filename << '\n';
    cout << "First operand digits: " << first.size() << '\n';
    cout << "Second operand digits: " << second.size() << '\n';

    auto start = Clock::now();

    string result = multiplyKaratsuba(first, second);

    auto end = Clock::now();

    double timeMs =
        chrono::duration<double, milli>(end - start).count();

    cout << "Result digits: " << result.size() << '\n';
    cout << "First 20 result digits: "
         << result.substr(0, 20) << '\n';
    cout << "Last 20 result digits: "
         << result.substr(result.size() > 20
                              ? result.size() - 20 : 0)
         << '\n';

    cout << fixed << setprecision(3);
    cout << "Execution time: " << timeMs << " ms\n";

    // Verify against schoolbook multiplication for small operands.
    if (first.size() <= 10000 && second.size() <= 10000) {
        string expected = schoolbookMultiply(first, second);

        bool correct = (expected == result);

        cout << "Correctness: "
             << (correct ? "PASS" : "FAIL") << '\n';

        if (!correct) {
            throw runtime_error("Karatsuba correctness check failed.");
        }
    } else {
        cout << "Correctness: Not independently checked "
             << "(large operands).\n";
    }

    saveResult(
        "Karatsuba",
        fs::path(filename).filename().string(),
        max(first.size(), second.size()),
        timeMs,
        "Result has " + to_string(result.size()) + " digits"
    );
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            cout << "Usage:\n";
            cout << "BenchmarkRunner.exe closest <dataset.txt>\n";
            cout << "BenchmarkRunner.exe multiply <dataset.txt>\n";
            return 1;
        }

        string mode = argv[1];
        string filename = argv[2];

        if (mode == "closest") {
            runClosestPair(filename);
        } else if (mode == "multiply") {
            runMultiplication(filename);
        } else {
            throw invalid_argument(
                "Unknown mode. Use closest or multiply."
            );
        }

        cout << "\nBenchmark completed successfully.\n";

    } catch (const exception& e) {
        cerr << "\nError: " << e.what() << '\n';
        return 1;
    }

    return 0;
}