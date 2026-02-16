#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
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
	const auto& pos = m_transform.GetPosition();
	
	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransfrom() const
{
	return m_transform;
}

//template<typename T, typename... Args>
//T* dae::GameObject::AddComponent(Args&&... args)
//{
//	static_assert(std::is_base_of<Component, T>::value,
//		"T must derive from Component");
//
//	auto component = std::make_unique<T>(std::forward<Args>(args)...);
//	component->owner = this;
//
//	T* rawPtr = component.get();
//	m_pComponents.emplace_back(std::move(component));
//
//	return rawPtr;
//}