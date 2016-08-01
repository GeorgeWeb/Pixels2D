#include "AudioEngine.h"
#include "Pixels2DErrors.h"

namespace Pixels2D
{
	void SoundEffect::play(int loops)
	{
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
			if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
				Errors::fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
			}
		}
	}

	void Music::play(int loops)
	{
		if (Mix_PlayMusic(m_music, loops) == -1)
			Errors::fatalError("Mix_PlayChannel error " + std::string(Mix_GetError()));
	}

	void Music::pause()
	{
		Mix_PauseMusic();
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}

	AudioEngine::AudioEngine()
	{
	}

	AudioEngine::~AudioEngine()
	{
		destroy();
	}

	void AudioEngine::init()
	{
		if (m_isInitialized)
			Errors::fatalError("Tried to initialize Audio Engine twice!\n");

		if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG | MIX_INIT_MP3) == -1)
			Errors::fatalError("Mix_Init error " + std::string(Mix_GetError()));
		
		if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
			Errors::fatalError("Mix_OpenAudio error " + std::string(Mix_GetError()));

		m_isInitialized = true;
	}

	void AudioEngine::destroy()
	{
		if (m_isInitialized)
		{
			m_isInitialized = false;
			
			for (auto &effect : m_effectMap)
				Mix_FreeChunk(effect.second);

			for (auto &music : m_musicMap)
				Mix_FreeMusic(music.second);

			m_effectMap.clear();
			m_musicMap.clear();

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string &filePath)
	{
		// try finding the audio in the cache
		auto effect = m_effectMap.find(filePath);

		SoundEffect soundEffect;

		if (effect == m_effectMap.end())
		{
			// failed to find it
			Mix_Chunk *chunk = Mix_LoadWAV(filePath.c_str());
			if(chunk == nullptr)
				Errors::fatalError("Mix_LoadWAV error " + std::string(Mix_GetError()));


			soundEffect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else
		{
			// it is already cached
			soundEffect.m_chunk = effect->second;
		}

		return soundEffect;
	}

	Music AudioEngine::loadMusic(const std::string &filePath)
	{
		// try finding the audio in the cache
		auto mit = m_musicMap.find(filePath);

		Music music;

		if (mit == m_musicMap.end())
		{
			// failed to find it
			Mix_Music *mixMusic = Mix_LoadMUS(filePath.c_str());
			if (mixMusic == nullptr)
				Errors::fatalError("Mix_LoadWAV error " + std::string(Mix_GetError()));


			music.m_music = mixMusic;
			m_musicMap[filePath] = mixMusic;
		}
		else
		{
			// it is already cached
			music.m_music = mit->second;
		}

		return music;
	}
}
