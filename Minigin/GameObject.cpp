#include "GameObject.h"
#include "Transform.h"

dae::GameObject::GameObject()
	: m_transform{ this }
{
}

dae::GameObject::~GameObject()
{
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->RemoveParent();
	}
}

void dae::GameObject::FixedUpdate(float)
{
}

void dae::GameObject::Update(float deltaTime)
{
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

void dae::GameObject::RenderUI()
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->RenderUI();
	}
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	// Check if pParent is valid
	if (IsChild(pParent) || pParent == this || m_pParent == pParent)
	{
		return;
	}

	// Store position
	if (pParent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetWorldPosition() - pParent->GetWorldPosition());
		}
		SetPositionDirty();
	}

	// Remove itself from previous parent
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	// Update parent and add child in new parent
	m_pParent = pParent;
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

void dae::GameObject::RemoveParent()
{
	SetParent(nullptr, true);
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	if (index >= 0 && index < static_cast<int>(m_pChildren.size()))
	{
		return m_pChildren[index];
	}

	return nullptr;
}

void dae::GameObject::SetLocalPosition(float x, float y, float z)
{
	m_transform.SetLocalPosition(x, y, z);
	SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_transform.SetLocalPosition(pos);
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	return m_transform.GetWorldPosition();
}

const dae::Transform* dae::GameObject::GetTransform() const
{
	return &m_transform;
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

void dae::GameObject::Destroy()
{
	m_markedForDestroy = true;

	for (auto& pChild : m_pChildren)
	{
		pChild->Destroy();
	}
}

bool dae::GameObject::IsDestroyed() const
{
	return m_markedForDestroy;
}

void dae::GameObject::SetPositionDirty()
{
	m_transform.SetPositionDirty();

	for (auto& pChild : m_pChildren)
	{
		pChild->SetPositionDirty();
	}
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.emplace_back(std::move(pChild));
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);

	if (it != m_pChildren.end())
	{
		m_pChildren.erase(it);
	}
}

bool dae::GameObject::IsChild(GameObject* pChild)
{
	for (const auto& child : m_pChildren)
	{
		if (pChild == child)
		{
			return true;
		}
	}

	return false;
}
