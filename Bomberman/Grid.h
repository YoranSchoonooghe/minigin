#pragma once
#include <glm/glm.hpp>

namespace dae
{
    struct Grid
    {
        float cellSize = 1.0f;
        int rows = 0;
        int cols = 0;
        glm::vec2 offset{ 0.0f, 0.0f };
    };

    struct Cell
    {
        int row;
        int col;
    };
}