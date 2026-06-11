#pragma once
#include <memory>
#include <string>

namespace dae
{
	class GameObject;

	namespace EnemyFactory
	{
		std::unique_ptr<GameObject> CreateBalloom();
		std::unique_ptr<GameObject> CreateOneal();
		std::unique_ptr<GameObject> CreateDoll();
		std::unique_ptr<GameObject> CreateMinvo();
		std::unique_ptr<GameObject> CreateEnemy(const std::string& enemyType);
	}

	namespace BombFactory
	{
		std::unique_ptr<GameObject> CreateBomb();
		std::unique_ptr<GameObject> CreateExplosion();
	}
}