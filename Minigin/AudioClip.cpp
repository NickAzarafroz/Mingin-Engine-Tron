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

void AudioClip::Load(const std::string filePath)
{
	const int frequency = 44100;
	const int chunkSize = 4096;
	const int channels = 2;
	const int audioFormat = AUDIO_S16SYS;

	std::cout << filePath << std::endl;


	if (Mix_OpenAudio(frequency, audioFormat, channels, chunkSize) != 0) {
		// Handle error
		std::cout << "Failed to open audio device: " << Mix_GetError() << std::endl;
		return;
	}

	m_pMixChunk = Mix_LoadWAV(filePath.c_str());

	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + filePath + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cout << errorMsg;
		return;
	}
}

void AudioClip::SetVolume(float volume)
{
	Mix_VolumeChunk(m_pMixChunk, static_cast<int>(volume));
}

void AudioClip::Play(int loop)
{
	Mix_PlayChannel(-1, m_pMixChunk, loop);
}

void AudioClip::Stop()
{
	Mix_HaltChannel(-1);
}
