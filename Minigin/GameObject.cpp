#include "GameObject.h"
#include "Transform.h"

void dae::GameObject::FixedUpdate(float fixedDeltaTime)
{
	(void)fixedDeltaTime;
}

void dae::GameObject::Update(float deltaTime)
{
	(void)deltaTime;

	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update(deltaTime);
	}

	CleanupDestroyedComponents();
}

void dae::GameObject::Render() const
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}

void dae::GameObject::CleanupDestroyedComponents()
{
	m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(),
		[](const std::unique_ptr<Component>& pComp)
		{
			return pComp->IsDestroyed();
		}),
		m_pComponents.end()
	);
}
