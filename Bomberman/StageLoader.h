#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <unordered_map>
#include <filesystem>

using json = nlohmann::json;

namespace dae
{
	struct StageData
	{
		int bricks;
        std::unordered_map<std::string, int> enemies;
        std::string powerUp;
	};

    namespace StageLoader
    {
        StageData LoadStage(const std::filesystem::path& filePath)
        {
            std::ifstream file(filePath);

            if (!file.is_open())
            {
                std::cout << "Failed to open stage file: " << filePath << std::endl;
            }

            json jsonData{};
            file >> jsonData;

            StageData stage{};

            stage.bricks = jsonData.at("bricks").get<int>();

            for (const auto& enemy : jsonData.at("enemies"))
            {
                auto type = enemy.at("type").get<std::string>();
                auto count = enemy.at("count").get<int>();

                stage.enemies[type] = count;
            }

            stage.powerUp = jsonData.at("powerup").get<std::string>();

            return stage;
        }

    }
}