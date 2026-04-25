#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		explicit SDLSoundSystem();
		~SDLSoundSystem();

		void Play(const soundId id, const float volume) override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}