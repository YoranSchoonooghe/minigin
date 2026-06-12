#pragma once
#include "GameState.h"
#include "Events/Observer.h"

namespace dae
{
	class NameEntryComponent;
	class Subject;

	class NameEntryState final : public GameState, public Observer
	{
	public:
		explicit NameEntryState() = default;
		~NameEntryState();
		NameEntryState(const NameEntryState& other) = delete;
		NameEntryState(NameEntryState&& other) = delete;
		NameEntryState& operator=(const NameEntryState& other) = delete;
		NameEntryState& operator=(NameEntryState&& other) = delete;

		void Enter() override;
		void Exit() override;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void LoadScene();
		void UnbindCommands();

		NameEntryComponent* m_pNameEntryComponent{ nullptr };
		Subject* m_pNameEntrySubject{ nullptr };
	};
}