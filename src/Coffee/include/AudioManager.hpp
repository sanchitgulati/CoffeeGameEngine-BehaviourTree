#pragma once

#include "../preprocessor/Common.h"
#include<SDL.h>
#include<SDL_mixer.h>
#include <iostream>
#include<memory>
#include <algorithm>
#include <map>
#include "SDL_thread.h"

namespace Coffee {

	class AudioManager_
	{
	private:
		std::string _currentMusic;
		Mix_Music* _music;
		std::map<std::string,Mix_Chunk*> _sfxLib;
		int _totalChannels;
		int _channelLooper;
	public:
		void preloadSfx(std::string& filepath);
		void preloadMusic(std::string& filepath);
		void playMusic(std::string& filepath);
		void playAudio(std::string&  filepath);
		void stopMusic(float fadeoutInSecs = -1);
		void stopAllSfx(int ms);
		void init(int totalChannels);
		void cleanup();
	private:
		COFFEE_MAKE_SINGLETON(AudioManager_);
	};
}
#define AudioManager AudioManager_::getInstance()


