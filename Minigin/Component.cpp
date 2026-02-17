#include "Component.h"

void dae::Component::FixedUpdate(float fixedDeltaTime)
{
	(void)fixedDeltaTime;
}

void dae::Component::Update(float deltaTime)
{
	(void)deltaTime;
}

void dae::Component::Render() const
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
