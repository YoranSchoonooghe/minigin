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
#include "Events/EventManager.h"

dae::BombComponent::BombComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	m_pCollider = GetOwner()->GetComponent<BoxColliderComponent>();
	assert(m_pCollider != nullptr && "BombComponent: GameObject is missing a BoxColliderComponent!");

	m_pColliderComponentSubject = m_pCollider->GetSubject();
	m_pColliderComponentSubject->AddObserver(this);

	auto* pTimer = GetOwner()->GetComponent<TimerComponent>();
	assert(pTimer != nullptr && "BombComponent: GameObject is missing a TimerComponent!");

	m_pTimerComponentSubject = pTimer->GetTimerSubject();
	m_pTimerComponentSubject->AddObserver(this);
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
		auto* pCollider = GetOwner()->GetComponent<BoxColliderComponent>();
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
		bool hitBorder{ false };

		for (int range{ 1 }; range <= GameManager::GetInstance().GetPowerUpData().flameRange; ++range)
		{
			Cell neighborCell{ bombCell.row + range * static_cast<int>(direction.y),
				bombCell.col + range * static_cast<int>(direction.x) };

			if (LevelUtils::IsPillarOrBorder(grid, neighborCell))
			{
				hitBorder = true;
				break;
			}
		
			auto pExplosion{ BombFactory::CreateExplosion() };
			auto position = GridUtils::GetPositionFromCell(grid, neighborCell);
			pExplosion->SetLocalPosition(position.x, position.y);
			auto* pExplosionComponent = pExplosion->AddComponent<dae::ExplosionComponent>();
			if (pExplosionComponent->HitBrick())
			{
				hitBorder = true;
				break;
			}

			auto* pScene = SceneManager::GetInstance().GetActiveScene();
			pScene->Add(std::move(pExplosion));
		}

		if (hitBorder) continue;
	}

	//GetOwner()->Destroy();
	GetOwner()->SetActive(false);
	m_pCollider->SetTrigger(true);
}
