#pragma once
#include <string>
#include <vector>
#include <utility> // for std::pair

class ScoreManager {
public:
    // Save a player's name and score to file
    static void saveScore(const std::string& name, int score, const std::string& filename = "players.txt");

    // Load all scores from file, returns vector of (name, score)
    static std::vector<std::pair<std::string, int>> loadScores(const std::string& filename = "players.txt");
};
