#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		explicit Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void FixedUpdate(float fixedDeltaTime);
		virtual void Update(float deltaTime);
		virtual void Render() const;

	protected:
		GameObject* owner = nullptr;

	private:
		friend class GameObject;
	};
}