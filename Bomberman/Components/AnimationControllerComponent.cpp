#include "AnimationControllerComponent.h"
#include "AnimatedSpriteComponent.h"
#include "CharacterControllerComponent.h"
#include "GameObject.h"
#include <cassert>

dae::AnimationControllerComponent::AnimationControllerComponent(GameObject* pOwner, const SpritesheetMoveDirection& animationDirection, bool moveWhenIdle)
	: Component{ pOwner }
	, m_animationDirection{ animationDirection }, m_moveWhenIdle{ moveWhenIdle }
{
	m_pAnimatedSpriteComponent = GetOwner()->GetComponent<AnimatedSpriteComponent>();

	assert(m_pAnimatedSpriteComponent != nullptr && "AnimationControllerComponent: GameObject is missing a AnimatedSpriteComponent!");

	auto pCharacterController = GetOwner()->GetComponent<CharacterControllerComponent>();
	if (pCharacterController)
	{
		m_pCharacterControllerComponentSubject = pCharacterController->GetSubject();
		m_pCharacterControllerComponentSubject->AddObserver(this);
	}
}

dae::AnimationControllerComponent::~AnimationControllerComponent()
{
	if (m_pCharacterControllerComponentSubject)
	{
		m_pCharacterControllerComponentSubject->RemoveObserver(this);
	}
}

void dae::AnimationControllerComponent::UpdateDirection(const glm::vec2& moveDirection)
{
	if (!m_pAnimatedSpriteComponent) return;

	if (moveDirection == glm::vec2(-1, 0))
		m_pAnimatedSpriteComponent->SetRow(m_animationDirection.left);
	else if (moveDirection == glm::vec2(1, 0))
		m_pAnimatedSpriteComponent->SetRow(m_animationDirection.right);
	else if (moveDirection == glm::vec2(0, -1))
		m_pAnimatedSpriteComponent->SetRow(m_animationDirection.up);
	else if (moveDirection == glm::vec2(0, 1))
		m_pAnimatedSpriteComponent->SetRow(m_animationDirection.down);
}

void dae::AnimationControllerComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnStartedMoving"):
		if (!m_moveWhenIdle)
			m_pAnimatedSpriteComponent->Play();
		break;
	case make_sdbm_hash("OnStoppedMoving"):
		if (!m_moveWhenIdle)
			m_pAnimatedSpriteComponent->Pause();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pCharacterControllerComponentSubject = nullptr;
		break;
	}
}
