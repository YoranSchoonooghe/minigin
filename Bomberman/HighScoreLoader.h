#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <filesystem>
#include <vector>

using json = nlohmann::json;

namespace dae
{
    struct HighScore
    {
        std::string name;
        int score;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        HighScore,
        name,
        score
    )

    namespace HighScoreLoader
    {
        inline std::vector<HighScore> LoadHighScores(const std::filesystem::path& filePath)
        {
            std::ifstream file(filePath);

            if (!file.is_open())
            {
                std::cout << "Failed to open stage file: " << filePath << std::endl;
            }

            json jsonData{};
            file >> jsonData;

            std::vector<HighScore> highscores;

            for (const auto& highScoreData : jsonData)
            {
                HighScore highScore{};

                highScore.name = highScoreData.at("name").get<std::string>();
                highScore.score = highScoreData.at("score").get<int>();

                highscores.push_back(highScore);
            }

            return highscores;
        }
    }
}