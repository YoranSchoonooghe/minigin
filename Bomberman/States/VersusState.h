#pragma once
#include "GameState.h"
#include "Events/Observer.h"
#include <vector>

namespace dae
{
	class VersusState final : public GameState
	{
	public:
		explicit VersusState() = default;
		~VersusState() = default;
		VersusState(const VersusState& other) = delete;
		VersusState(VersusState&& other) = delete;
		VersusState& operator=(const VersusState& other) = delete;
		VersusState& operator=(VersusState&& other) = delete;

		void Enter() override;
		void Exit() override;

	private:
		void LoadScene();
		void UnbindCommands();

		std::vector<GameObject*> m_bombsPool;
	};
}