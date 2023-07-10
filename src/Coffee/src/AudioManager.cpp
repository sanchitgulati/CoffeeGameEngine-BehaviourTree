#include "../include/AudioManager.hpp"

namespace Coffee{
	void AudioManager_::preloadSfx(std::string& filepath)
	{
		auto sfx = Mix_LoadWAV(filepath.c_str());
		if (sfx == NULL)
			printf("Failed to load SFX - %s (%s)\n",filepath.c_str(), Mix_GetError());
		else
		{
			_sfxLib[filepath] = sfx;
		}
	}
	void AudioManager_::preloadMusic(std::string& filepath)
	{
		_music = Mix_LoadMUS(filepath.c_str());
		if (_music == NULL)
			printf("Failed to load Music (%s)\n", Mix_GetError());
	}
	void AudioManager_::playMusic(std::string& filepath)
	{
		if (_currentMusic.compare(filepath) != 0)
		{
			preloadMusic(filepath);
		}

		if (Mix_PlayMusic(_music, -1) == -1)
			printf("Failed to play Music (%s)\n", Mix_GetError());
	}

	void AudioManager_::playAudio(std::string &filepath)
	{
		if (_sfxLib.find(filepath) == _sfxLib.end())
		{
			preloadSfx(filepath);
		}
		if (Mix_PlayChannel(_channelLooper++, _sfxLib[filepath], 0) == -1)
			printf("Failed to play SFX - %s (%s)\n", filepath.c_str(), Mix_GetError());

		if (_channelLooper >= _totalChannels)
			_channelLooper = 0;

	}
	void AudioManager_::stopMusic(float fadeoutInSecs)
	{
		if (fadeoutInSecs == -1)
			Mix_HaltMusic();
		else
			Mix_FadeOutMusic(static_cast<int>(fadeoutInSecs *1000));
	}

	void AudioManager_::stopAllSfx(int ms = 10)
	{
		for (int i = 0; i < _totalChannels; i++) {
			Mix_FadeOutChannel(i, ms);
		}
	}

	void AudioManager_::init(int totalChannels)
	{
		_totalChannels = totalChannels;
		_channelLooper = 0;
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, _totalChannels, 4096) == -1)
			printf("Failed to initialize Audio Mixer (%s)\n", Mix_GetError());
	}
	void AudioManager_::cleanup()
	{
		Mix_FreeMusic(_music);
		stopAllSfx(0);
		std::map<std::string, Mix_Chunk*>::iterator it = _sfxLib.begin();
		while (it != _sfxLib.end())
		{
			if(it->second != NULL)
				Mix_FreeChunk(it->second);
			it++;
		}
		_sfxLib.clear();
	}
}