#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void Play(const soundId, const float) override {}
	};

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *m_soundSystem; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
		{
			m_soundSystem = soundSystem == nullptr ? std::make_unique<NullSoundSystem>() : std::move(soundSystem);
		}

	private:
		static std::unique_ptr<SoundSystem> m_soundSystem;
	};
}