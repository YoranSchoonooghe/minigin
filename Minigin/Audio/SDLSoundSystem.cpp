#include "SDLSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>

namespace dae
{
	class SDLSoundSystem::SDLSoundSystemImpl
	{
	public:
		explicit SDLSoundSystemImpl()
		{
			m_pMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
			if (!m_pMixer)
			{
				SDL_Log("MIX_CreateMixerDevice error: %s", SDL_GetError());
			}

			m_pTrack = MIX_CreateTrack(m_pMixer);
			if (!m_pTrack)
			{
				SDL_Log("MIX_CreateTrack error: %s", SDL_GetError());
			}
		}

		void Play(const soundId, const float)
		{
			auto audio = MIX_LoadAudio(m_pMixer, "Data/Audio/StageStart.wav", false);
			if (!audio)
			{
				SDL_Log("MIX_LoadAudio error: %s", SDL_GetError());
			}

			MIX_SetTrackAudio(m_pTrack, audio);
			MIX_PlayTrack(m_pTrack, 0);
		}

	private:
		MIX_Mixer* m_pMixer{};
		MIX_Track* m_pTrack{};
	};

	SDLSoundSystem::SDLSoundSystem()
		: m_pImpl(std::make_unique<SDLSoundSystemImpl>())
	{
	}

	SDLSoundSystem::~SDLSoundSystem() = default;

	void SDLSoundSystem::Play(const soundId id, const float volume)
	{
		return m_pImpl->Play(id, volume);
	}
}