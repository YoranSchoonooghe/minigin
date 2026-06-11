#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Components/Component.h"
#include <string>

namespace dae
{
	class GameObject final
	{
	public:
		explicit GameObject(const std::string& name = "GameObject");
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render() const;
		void RenderUI();

		void SetParent(GameObject* pParent, bool keepWorldPosition = true);
		void RemoveParent();
		GameObject* GetParent() const { return m_pParent; };
		int GetChildCount() const { return static_cast<int>(m_pChildren.size()); };
		GameObject* GetChildAt(int index) const;

		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition();
		const glm::vec3& GetWorldPosition();
		//Transform* GetTransform() const;

		std::vector<Component*> GetComponents() const;

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);
		template<typename T>
		bool HasComponent();
		template<typename T>
		void RemoveComponent();
		template<typename T>
		T* GetComponent();

		void CleanupDestroyedComponents();
		void Destroy();
		bool IsDestroyed() const;

		std::string GetName() const;
		
		bool IsActive() const { return m_isActive; }
		void SetActive(bool active);

	private:
		void SetPositionDirty();
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		bool IsChild(GameObject* pChild);

		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{};

		std::unique_ptr<Transform> m_pTransform;

		std::vector<std::unique_ptr<Component>> m_pComponents{};
		bool m_markedForDestroy{ false };

		std::string m_name;
		bool m_isActive{ true };
	};

#pragma region TemplateFunctions
	template<typename T, typename ...Args>
	inline T* GameObject::AddComponent(Args && ...args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		auto pComponent = std::make_unique<T>(this, std::forward<Args>(args)...);

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
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		for (auto& pComponent : m_pComponents)
		{
			if (auto casted = dynamic_cast<T*>(pComponent.get()))
			{
				return casted;
			}
		}
		return nullptr;
	}
#pragma endregion
}