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