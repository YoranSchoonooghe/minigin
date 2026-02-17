#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class GameObject final
	{
	public:
		explicit GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		Transform GetTransform() const;
		glm::mat2x3 matrix{};

		void CleanupDestroyedComponents();

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);

		template<typename T>
		bool HasComponent();

		template<typename T>
		void RemoveComponent();

		template<typename T>
		T* GetComponent();

	private:
		Transform m_transform{};
		std::vector<std::unique_ptr<Component>> m_pComponents{};
	};

	template<typename T, typename ...Args>
	inline T* GameObject::AddComponent(Args && ...args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		auto pComponent = std::make_unique<T>(std::forward<Args>(args)...);
		pComponent->owner = this;

		T* rawPtr = pComponent.get();
		m_pComponents.emplace_back(std::move(pComponent));

		return rawPtr;
	}

	template<typename T>
	inline bool GameObject::HasComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		for (auto& pComp : m_pComponents)
		{
			if (auto casted = dynamic_cast<T*>(pComp.get()))
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		for (auto& pComp : m_pComponents)
		{
			if (auto casted = dynamic_cast<T*>(pComp.get()))
			{
				casted->Destroy();
			}
		}
	}

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (auto& pComponent : m_pComponents)
		{
			if (auto casted = dynamic_cast<T*>(pComponent.get()))
			{
				return casted;
			}
		}
		return nullptr;
	}
}
