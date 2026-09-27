#include "freeze.h"
#include <fstream>
#include <iostream>
#include <sstream>

void ScoreManager::saveScore(const std::string& name, int score, const std::string& filename) {
    std::ofstream file(filename, std::ios::app); // append mode
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << " for writing.\n";
        return;
    }
    file << name << ", " << score << "\n";
    file.close();
}

std::vector<std::pair<std::string, int>> ScoreManager::loadScores(const std::string& filename) {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << " for reading.\n";
        return scores; // empty vector
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        int score = 0;
        if (std::getline(ss, name, ',') && ss >> score) {
            // remove leading/trailing spaces from name
            if (!name.empty() && name[0] == ' ') name.erase(0, 1);
            scores.emplace_back(name, score);
        }
    }

    file.close();
    return scores;
}
