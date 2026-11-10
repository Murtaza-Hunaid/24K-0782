#include <algorithm>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;
namespace fs = std::filesystem;

struct Point {
    double x, y;
};

const uint64_t CP_SEED = 20261100;
const uint64_t IM_SEED = 20261200;

mt19937_64 cpRng(CP_SEED);
mt19937_64 imRng(IM_SEED);

vector<string> seedLog;

double randomReal(double low, double high) {
    uniform_real_distribution<double> dist(low, high);
    return dist(cpRng);
}

int randomInt(int low, int high) {
    uniform_int_distribution<int> dist(low, high);
    return dist(cpRng);
}

string randomNumber(size_t digits) {
    string number;
    number.reserve(digits);

    uniform_int_distribution<int> firstDigit(1, 9);
    uniform_int_distribution<int> otherDigit(0, 9);

    number += char('0' + firstDigit(imRng));

    for (size_t i = 1; i < digits; ++i) {
        number += char('0' + otherDigit(imRng));
    }

    return number;
}

void seedClosestPair(int fileNumber) {
    uint64_t seed = CP_SEED + fileNumber;

    cpRng.seed(seed);

    char label[20];
    snprintf(label, sizeof(label), "cp%02d", fileNumber);

    seedLog.push_back(string(label) + " seed: " + to_string(seed));
}

void seedIntegerMultiplication(int fileNumber) {
    uint64_t seed = IM_SEED + fileNumber;

    imRng.seed(seed);

    char label[20];
    snprintf(label, sizeof(label), "im%02d", fileNumber);

    seedLog.push_back(string(label) + " seed: " + to_string(seed));
}

void savePoints(const fs::path& file, const vector<Point>& points) {
    ofstream out(file);

    if (!out) {
        throw runtime_error("Could not create " + file.string());
    }

    out << points.size() << '\n';
    out << setprecision(17);

    for (const auto& p : points) {
        out << p.x << ' ' << p.y << '\n';
    }

    cout << "Created " << file.string()
         << " (" << points.size() << " points)\n";
}

void saveNumbers(const fs::path& file,
                 const string& first,
                 const string& second) {
    ofstream out(file);

    if (!out) {
        throw runtime_error("Could not create " + file.string());
    }

    out << first << '\n' << second << '\n';

    cout << "Created " << file.string()
         << " (" << first.size() << " and "
         << second.size() << " digits)\n";
}

void generateClosestPair(const fs::path& folder) {
    cout << "\nGenerating Closest Pair datasets...\n";

    // cp01-cp04: Uniform random points.
    const vector<int> sizes = {1000, 10000, 100000, 1000000};

    for (int i = 0; i < 4; ++i) {
        seedClosestPair(i + 1);

        vector<Point> points;
        points.reserve(sizes[i]);

        for (int j = 0; j < sizes[i]; ++j) {
            points.push_back({
                randomReal(0, 1000000),
                randomReal(0, 1000000)
            });
        }

        char filename[20];
        snprintf(filename, sizeof(filename), "cp%02d.txt", i + 1);
        savePoints(folder / filename, points);
    }

    // cp05: One million points around ten random centers.
    {
        seedClosestPair(5);

        vector<Point> points;
        points.reserve(1000000);

        vector<Point> centers;

        for (int i = 0; i < 10; ++i) {
            centers.push_back({
                randomReal(100000, 900000),
                randomReal(100000, 900000)
            });
        }

        normal_distribution<double> offset(0, 1500);

        for (int i = 0; i < 1000000; ++i) {
            const Point& center = centers[i % 10];

            double x = center.x + offset(cpRng);
            double y = center.y + offset(cpRng);

            x = clamp(x, 0.0, 1000000.0);
            y = clamp(y, 0.0, 1000000.0);

            points.push_back({x, y});
        }

        savePoints(folder / "cp05.txt", points);
    }

    // cp06: Small integer coordinate range, producing duplicates.
    {
        seedClosestPair(6);

        vector<Point> points;
        points.reserve(1000000);

        for (int i = 0; i < 1000000; ++i) {
            points.push_back({
                static_cast<double>(randomInt(0, 100)),
                static_cast<double>(randomInt(0, 100))
            });
        }

        savePoints(folder / "cp06.txt", points);
    }

    // cp07: 100,000 points on one vertical line.
    {
        seedClosestPair(7);

        vector<Point> points;
        points.reserve(100000);

        for (int i = 0; i < 100000; ++i) {
            points.push_back({42.0, i * 10.0});
        }

        savePoints(folder / "cp07.txt", points);
    }

    // cp08: 400 x 250 equally spaced grid.
    {
        seedClosestPair(8);

        vector<Point> points;
        points.reserve(100000);

        for (int row = 0; row < 250; ++row) {
            for (int col = 0; col < 400; ++col) {
                points.push_back({
                    col * 10.0,
                    row * 10.0
                });
            }
        }

        savePoints(folder / "cp08.txt", points);
    }

    // cp09: Closest pair lies across x = 0.
    {
        seedClosestPair(9);

        vector<Point> points;
        points.reserve(1000000);

        for (int i = 0; i < 499999; ++i) {
            points.push_back({-1000.0, i * 4.0});
            points.push_back({1000.0, i * 4.0 + 2.0});
        }

        points.push_back({-0.5, 0.0});
        points.push_back({0.5, 0.0});

        shuffle(points.begin(), points.end(), cpRng);
        savePoints(folder / "cp09.txt", points);
    }

    // cp10: Small dataset for visualization.
    {
        seedClosestPair(10);

        vector<Point> points;

        for (int i = 0; i < 101; ++i) {
            points.push_back({
                randomReal(0, 100),
                randomReal(0, 100)
            });
        }

        savePoints(folder / "cp10.txt", points);
    }
}

void generateIntegerMultiplication(const fs::path& folder) {
    cout << "\nGenerating Integer Multiplication datasets...\n";

    // im01-im04: Random numbers of increasing digit lengths.
    const vector<size_t> sizes = {
        1000, 10000, 100000, 1000000
    };

    for (int i = 0; i < 4; ++i) {
        seedIntegerMultiplication(i + 1);

        char filename[20];
        snprintf(filename, sizeof(filename), "im%02d.txt", i + 1);

        saveNumbers(
            folder / filename,
            randomNumber(sizes[i]),
            randomNumber(sizes[i])
        );
    }

    // im05: Unequal operand lengths.
    seedIntegerMultiplication(5);

    saveNumbers(
        folder / "im05.txt",
        randomNumber(1000000),
        randomNumber(10)
    );

    // im06: One operand consists entirely of nines.
    seedIntegerMultiplication(6);

    saveNumbers(
        folder / "im06.txt",
        string(100000, '9'),
        randomNumber(100000)
    );

    // im07: Odd-length operands containing many zeros.
    {
        seedIntegerMultiplication(7);

        string first, second;

        first.reserve(99999);
        second.reserve(99999);

        for (int i = 0; i < 99999; ++i) {
            first += (i % 5 == 0) ? '1' : '0';
            second += (i % 7 == 0) ? '3' : '0';
        }

        saveNumbers(folder / "im07.txt", first, second);
    }

    // im08: Two one-million-digit powers of ten.
    seedIntegerMultiplication(8);

    saveNumbers(
        folder / "im08.txt",
        "1" + string(999999, '0'),
        "1" + string(999999, '0')
    );

    // im09: One zero operand and one million-digit operand.
    seedIntegerMultiplication(9);

    saveNumbers(
        folder / "im09.txt",
        "0",
        randomNumber(1000000)
    );

    // im10: Small dataset for visualization.
    seedIntegerMultiplication(10);

    saveNumbers(
        folder / "im10.txt",
        randomNumber(101),
        randomNumber(101)
    );
}

void saveSeeds(const fs::path& file) {
    fs::create_directories(file.parent_path());

    ofstream out(file);

    if (!out) {
        throw runtime_error("Could not create " + file.string());
    }

    for (const auto& line : seedLog) {
        out << line << '\n';
    }
}

int main(int argc, char* argv[]) {
    try {
        fs::path output = (argc >= 2) ? argv[1] : "datasets";

        fs::path closestFolder = output / "closest_pair";
        fs::path integerFolder = output / "integer_multiplication";

        fs::create_directories(closestFolder);
        fs::create_directories(integerFolder);

        generateClosestPair(closestFolder);
        generateIntegerMultiplication(integerFolder);

        saveSeeds("DatasetGenerator/seeds.txt");

        cout << "\nAll 20 datasets generated successfully.\n";
        cout << "Output folder: " << fs::absolute(output) << '\n';

    } catch (const exception& e) {
        cerr << "\nError: " << e.what() << '\n';
        return 1;
    }

    return 0;
}