#pragma once
#include "Grid.h"
#include <vector>

namespace dae
{
	namespace GridUtils
	{
		inline glm::vec2 GetPositionFromCell(const Grid& grid, int row, int col)
		{
			glm::vec2 position{};

			position.x = grid.offset.x + col * grid.cellSize;
			position.y = grid.offset.y + row * grid.cellSize;

			return position;
		}
	}

	namespace LevelUtils
	{
		inline std::vector<Cell> GetValidBrickCells(const Grid& grid)
		{
			std::vector<Cell> validCells{};

			int const nrOfPillars{ (grid.cols - 2) / 2 * (grid.rows - 2) / 2 };
			int const nrOfFreeCellsAroundPlayer{ 3 };
			validCells.reserve((grid.rows - 2) * (grid.cols - 2) - nrOfPillars - nrOfFreeCellsAroundPlayer);

			for (int row{ 1 }; row < grid.rows - 1; ++row)
			{
				for (int col{ 1 }; col < grid.cols - 1; ++col)
				{
					if ((row == 1 && col == 1) 
						|| (row == 1 && col == 2) 
						|| (row == 2 && col == 1)) 
						continue;

					if (row % 2 == 0 && col % 2 == 0) continue;

					validCells.emplace_back(row, col);
				}
			}

			return validCells;
		}

	}
}