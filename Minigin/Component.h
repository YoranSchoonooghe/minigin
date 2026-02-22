#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void FixedUpdate(float fixedDeltaTime);
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void Destroy();
		bool IsDestroyed() const;

	protected:
		explicit Component(GameObject* pOwner) : m_pOwner{ pOwner } {};
		GameObject* GetOwner() const;

	private:
		GameObject* m_pOwner = nullptr;
		bool m_markedForDestroy = false;
	};
}