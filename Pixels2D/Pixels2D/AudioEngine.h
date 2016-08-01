#pragma once

#ifndef AUDIOENGINE_HGUARD
#define AUDIOENGINE_HGUARD

#include <SDL/SDL_mixer.h>

#include <string>
#include <map>

namespace Pixels2D
{
	class SoundEffect
	{
	public:
		friend class AudioEngine;
		
		// plays the effect audio file
		// @param loops: if loops == -1, loop forever
		// if loop == 0, play `once`
		// otherwise play it `loops+1` times (1, 2, 3...n)
		void play(int loops = 0);
	private:
		Mix_Chunk *m_chunk = nullptr;
	};

	class Music
	{
	public:
		friend class AudioEngine;

		// plays the music audio file
		// @param loops: if loops == -1, loop forever
		// otherwise play it `loops` times (0, 1, 2...n)
		void play(int loops = 1);

		static void pause();
		static void stop();
		static void resume();

	private:
		Mix_Music *m_music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

	public:
		SoundEffect loadSoundEffect(const std::string &filePath);
		Music loadMusic(const std::string &filePath);

	private:
		bool m_isInitialized = false;
		
		// used for effects cache
		std::map<std::string, Mix_Chunk*> m_effectMap;
		// used for music cache
		std::map<std::string, Mix_Music*> m_musicMap;
	};
}

#endif // !AUDIOENGINE_HGUARD