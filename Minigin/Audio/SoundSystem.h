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
		virtual void Destroy() = 0;

		virtual void Play(const SoundId id, const float volume = 1.0f, const bool loop = false) = 0;
		virtual void StopAll() = 0;
		virtual void Preload(const SoundId id) = 0;
		virtual void AddAudioSource(const AudioSource& audioSource) = 0;
		virtual void RemoveAudioSource(SoundId id) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
		void Destroy() override {};

		void Play(const SoundId, const float, const bool) override {}
		void StopAll() override {}
		void Preload(const SoundId) override {}
		void AddAudioSource(const AudioSource&) override {}
		void RemoveAudioSource(SoundId) override {}
	};
}
