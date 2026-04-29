#include "SDLSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <queue>
#include <unordered_map>
#include <mutex>

namespace dae
{
	class SDLSoundSystem::SDLSoundSystemImpl
	{
	public:
		explicit SDLSoundSystemImpl(const uint16_t tracks)
		{
			if (!MIX_Init())
			{
				SDL_Log("Mixer error: %s", SDL_GetError());
				throw std::runtime_error(std::string("Mix_Init Error: ") + SDL_GetError());
			}

			m_pMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
			if (!m_pMixer)
			{
				SDL_Log("MIX_CreateMixerDevice error: %s", SDL_GetError());
			}

			for (int i = 0; i < tracks; ++i)
			{
				auto pTrack = MIX_CreateTrack(m_pMixer);
				if (!pTrack)
				{
					SDL_Log("MIX_CreateTrack error: %s", SDL_GetError());
				}

				m_pTracks.push_back(pTrack);
			}

#ifndef __EMSCRIPTEN__
			m_soundThread = std::jthread(&SDLSoundSystemImpl::Process, this);
#endif
		}

		~SDLSoundSystemImpl()
		{
			m_quit = true;
			m_conditionVariable.notify_all();

			//MIX_StopAllTracks(m_pMixer, 0);
			//for (auto* pTrack : m_pTracks)
			//{
			//	MIX_DestroyTrack(pTrack);
			//}

			//MIX_DestroyMixer(m_pMixer);

			//MIX_Quit();
		}

		void Play(const SoundId id, const float)
		{
			{
				std::lock_guard<std::mutex> lockGuard(m_mutex);
				m_eventQueue.push(id);
			}

			m_conditionVariable.notify_one();
		}

		void AddAudioSource(const AudioSource& audioSource)
		{
			m_audioSources.insert({ audioSource.id, audioSource });
		}

		void RemoveAudioSource(const SoundId id)
		{
			m_audioSources.erase(id);
		}

		void Process()
		{
			while (!m_quit)
			{
				SoundId id{};

				{
					std::unique_lock<std::mutex> lockGuard(m_mutex);

					m_conditionVariable.wait(lockGuard,
						[this] { return !m_eventQueue.empty() || m_quit; }
					);

					if (m_eventQueue.empty() && m_quit) break;

					id = m_eventQueue.front();
					m_eventQueue.pop();
				}

				auto it = m_audioSources.find(id);
				if (it == m_audioSources.end()) continue;

				auto audio = MIX_LoadAudio(m_pMixer, it->second.filePath.c_str(), false);
				if (!audio)
				{
					SDL_Log("MIX_LoadAudio error: %s", SDL_GetError());
				}

				MIX_Track* pTrack = GetAvailableTrack();
				if (!pTrack)
				{
					SDL_Log("No available Track.");
					continue;
				}

				MIX_SetTrackAudio(pTrack, audio);
				MIX_PlayTrack(pTrack, 0);
			}
		}

		MIX_Track* GetAvailableTrack()
		{
			for (auto* pTrack : m_pTracks)
			{
				if (!MIX_TrackPlaying(pTrack))
				{
					return pTrack;
				}
			}

			return nullptr;
		}

	private:
		std::unordered_map<SoundId, AudioSource> m_audioSources{};

		MIX_Mixer* m_pMixer{};
		std::vector<MIX_Track*> m_pTracks{};

		std::queue<SoundId> m_eventQueue{};

		std::atomic<bool> m_quit{ false };
#ifndef __EMSCRIPTEN__
		std::jthread m_soundThread{};
#endif
		std::mutex m_mutex{};
		std::condition_variable m_conditionVariable{};
	};

	SDLSoundSystem::SDLSoundSystem(const uint16_t tracks)
		: m_pImpl(std::make_unique<SDLSoundSystemImpl>(tracks))
	{
	}

	SDLSoundSystem::~SDLSoundSystem() = default;

	void SDLSoundSystem::Play(const SoundId id, const float volume)
	{
		return m_pImpl->Play(id, volume);
	}
	void dae::SDLSoundSystem::AddAudioSource(const AudioSource& audioSource)
	{
		return m_pImpl->AddAudioSource(audioSource);
	}
	void dae::SDLSoundSystem::RemoveAudioSource(const SoundId id)
	{
		return m_pImpl->RemoveAudioSource(id);
	}
}