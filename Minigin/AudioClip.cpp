#include "AudioClip.h"
#include <iostream>
#include <SDL_mixer.h>
using namespace dae;

AudioClip::~AudioClip()
{
	Mix_FreeChunk(m_pMixChunk);
	m_pMixChunk = nullptr;
}

bool AudioClip::IsLoaded() const
{
	return m_pMixChunk != nullptr;
}

void AudioClip::Load(unsigned short id)
{
	//TODO: Change this. Only for testing if playing a sound works
	const std::string& filePath = "../Data/Dig_Dug_SFX_(11).wav";

	const int frequency = 44100;
	const int chunkSize = 4096;
	const int channels = 2;
	const int audioFormat = AUDIO_S16SYS;

	switch (id)
	{
	case 0: 
		std::cout << filePath << std::endl;
	}


	if (Mix_OpenAudio(frequency, audioFormat, channels, chunkSize) != 0) {
		// Handle error
		std::cerr << "Failed to open audio device: " << Mix_GetError() << std::endl;
		return;
	}

	m_pMixChunk = Mix_LoadWAV(filePath.c_str());

	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + filePath + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
		return;
	}
}

void AudioClip::SetVolume(float volume)
{
	Mix_VolumeChunk(m_pMixChunk, static_cast<int>(volume));
}

void AudioClip::Play()
{
	Mix_PlayChannel(-1, m_pMixChunk, 0);
}
