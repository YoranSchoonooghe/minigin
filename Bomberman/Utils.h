#pragma once
#include "Grid.h"
#include <vector>

namespace dae
{
	namespace DirectionUtils
	{
		inline std::vector<glm::vec2> GetAllDirections()
		{
			std::vector<glm::vec2> directions{};

			directions.push_back(glm::vec2(1, 0));
			directions.push_back(glm::vec2(-1, 0));
			directions.push_back(glm::vec2(0, 1));
			directions.push_back(glm::vec2(0, -1));

			return directions;
		}
	}

	namespace GridUtils
	{
		inline glm::vec2 GetPositionFromCell(const Grid& grid, int row, int col)
		{
			glm::vec2 position{};

			position.x = grid.offset.x + col * grid.cellSize;
			position.y = grid.offset.y + row * grid.cellSize;

			return position;
		}

		inline glm::vec2 GetPositionFromCell(const Grid& grid, const Cell& cell)
		{
			return GetPositionFromCell(grid, cell.row, cell.col);
		}

		inline bool IsBorderCell(const Grid& grid, const Cell& cell)
		{
			if (cell.row == 0 || cell.row == grid.rows - 1)
				return true;

			if (cell.col == 0 || cell.col == grid.cols - 1)
				return true;

			return false;
		}

		inline Cell GetCellFromPosition(const Grid& grid, const glm::vec3& position)
		{
			Cell cell{};

			cell.col = static_cast<int>((position.x - grid.offset.x) / grid.cellSize);
			cell.row = static_cast<int>((position.y - grid.offset.y) / grid.cellSize);

			return cell;
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


		inline bool IsPillarOrBorder(const Grid& grid, const Cell& cell)
		{
			if (GridUtils::IsBorderCell(grid, cell))
				return true;

			if (cell.row % 2 == 0 && cell.col % 2 == 0)
				return true;

			return false;
		}
	}

	namespace CollisionUtils
	{
		enum class Layer : uint8_t
		{
			Level = 0b0000'0001,
			Player = 0b0000'0010,
			Enemy = 0b0000'0100,
			Brick = 0b0000'1000,
			Bomb = 0b0001'0000,
			Explosion = 0b0010'0000,
			Exit = 0b0100'0000,
			PowerUp = 0b1000'0000
		};
	}
}