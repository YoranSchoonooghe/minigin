#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(GameObject* pOwner, const glm::vec3& position)
	: Component(pOwner)
	, m_worldPosition{ position }, m_localPosition{ position }
{
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_positionIsDirty)
	{
		UpdateWorldPosition();
	}

	return m_worldPosition;
}

void dae::Transform::SetLocalPosition(float x, float y, float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
}

void dae::Transform::SetLocalPosition(const glm::vec3& localPosition)
{
	m_localPosition = localPosition;
}

void dae::Transform::SetPositionDirty()
{
	m_positionIsDirty = true;
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_positionIsDirty)
	{
		const auto pParent = GetOwner()->GetParent();
		if (pParent == nullptr)
		{
			m_worldPosition = m_localPosition;
		}
		else
		{
			m_worldPosition = pParent->GetWorldPosition() + m_localPosition;
		}
	}
	m_positionIsDirty = false;
}
