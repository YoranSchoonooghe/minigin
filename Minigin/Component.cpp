#include "Component.h"
#include "GameObject.h"

void dae::Component::FixedUpdate(float)
{
}

void dae::Component::Update(float)
{
}

void dae::Component::Render() const
{
}

void dae::Component::RenderUI()
{
}

void dae::Component::Destroy()
{
	m_markedForDestroy = true;
}

bool dae::Component::IsDestroyed() const
{
	return m_markedForDestroy;
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}
