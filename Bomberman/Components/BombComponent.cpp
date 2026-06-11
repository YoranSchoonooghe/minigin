#include "BombComponent.h"
#include "Events//Subject.h"
#include "Components/BoxColliderComponent.h"
#include "Components/TimerComponent.h"
#include <cassert>
#include "Audio/ServiceLocator.h"
#include "GameObject.h"
#include "Components/ExplosionComponent.h"
#include "Utils.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Factory.h"

dae::BombComponent::BombComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	const auto& pCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pCollider != nullptr && "BombComponent: GameObject is missing a BoxColliderComponent!");

	m_pColliderComponentSubject = pCollider->GetSubject();
	m_pColliderComponentSubject->AddObserver(this);

	const auto& pTimer = GetOwner()->GetComponent<TimerComponent>();

	assert(pTimer != nullptr && "BombComponent: GameObject is missing a TimerComponent!");

	m_pTimerComponentSubject = pTimer->GetTimerSubject();
	m_pTimerComponentSubject->AddObserver(this);

	ServiceLocator::GetSoundSystem().Play(2);
}

dae::BombComponent::~BombComponent()
{
	if (m_pColliderComponentSubject)
	{
		m_pColliderComponentSubject->RemoveObserver(this);
	}
	if (m_pTimerComponentSubject)
	{
		m_pTimerComponentSubject->RemoveObserver(this);
	}
}

void dae::BombComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTriggerExit"):
	{
		const auto& pCollider = GetOwner()->GetComponent<BoxColliderComponent>();
		pCollider->SetTrigger(false);
	}
		break;
	case make_sdbm_hash("OnTimerFinished"):
		Explode();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pColliderComponentSubject = nullptr;
		m_pTimerComponentSubject = nullptr;
		break;
	}
}

void dae::BombComponent::Explode()
{
	ServiceLocator::GetSoundSystem().Play(3, 2.0f);

	auto grid = GameManager::GetInstance().GetGrid();
	auto bombCell = GridUtils::GetCellFromPosition(grid, GetOwner()->GetWorldPosition());

	auto directions{ DirectionUtils::GetAllDirections() };
	directions.push_back(glm::vec2(0, 0));

	for (auto direction : directions)
	{
		Cell neighborCell{ bombCell.row + static_cast<int>(direction.x), bombCell.col + static_cast<int>(direction.y) };

		if (LevelUtils::IsPillarOrBorder(grid, neighborCell)) continue;
		
		auto pExplosion{ BombFactory::CreateExplosion() };
		auto position = GridUtils::GetPositionFromCell(grid, neighborCell);
		pExplosion->SetLocalPosition(position.x, position.y);
		pExplosion->AddComponent<dae::ExplosionComponent>();

		auto* pScene = SceneManager::GetInstance().GetActiveScene();
		pScene->Add(std::move(pExplosion));
	}

	GetOwner()->Destroy();
}
