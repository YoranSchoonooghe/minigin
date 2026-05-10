#pragma once
#include "SoundSystem.h"
#include <memory>
#include <string>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		explicit SDLSoundSystem(const uint16_t tracks = 8);
		~SDLSoundSystem();
		void Destroy() override;

		void Play(const SoundId id, const float volume, const bool loop) override;
		void StopAll() override;
		void Preload(const SoundId id) override;
		void AddAudioSource(const AudioSource& audioSource) override;
		void RemoveAudioSource(const SoundId id) override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}