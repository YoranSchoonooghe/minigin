#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class Texture2D;

	class GameObject 
	{
	public:
		explicit GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void FixedUpdate(float fixedDeltaTime);
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Transform GetTransfrom() const;
		glm::mat2x3 matrix{};

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value,
				"T must derive from Component");

			auto pComponent = std::make_unique<T>(std::forward<Args>(args)...);
			pComponent->owner = this;

			T* rawPtr = pComponent.get();
			m_pComponents.emplace_back(std::move(pComponent));

			return rawPtr;
		}

		template<typename T>
		T* GetComponent()
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

	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_pTexture{};
		std::vector<std::unique_ptr<Component>> m_pComponents{};
	};
}
