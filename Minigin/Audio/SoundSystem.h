#pragma once
#include <cstdint>
#include <string>

namespace dae
{
	using SoundId = uint16_t;

	struct AudioSource
	{
		SoundId id;
		std::string filePath;
	};

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const SoundId id, const float volume = 1.0f) = 0;
		virtual void Preload(const SoundId id) = 0;
		virtual void AddAudioSource(const AudioSource& audioSource) = 0;
		virtual void RemoveAudioSource(SoundId id) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
		void Play(const SoundId, const float) override {}
		void Preload(const SoundId) override {}
		void AddAudioSource(const AudioSource&) override {}
		void RemoveAudioSource(SoundId) override {}
	};
}
