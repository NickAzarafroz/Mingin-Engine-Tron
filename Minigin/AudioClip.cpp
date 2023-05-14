#include "AudioClip.h"
#include <iostream>
#include <SDL_mixer.h>
using namespace dae;

AudioClip::AudioClip(){}

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
	switch (id)
	{
	case 0:
		m_FilePath = "Sound.wav";
	}

	m_pMixChunk = Mix_LoadWAV(m_FilePath.c_str());

	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + m_FilePath + ",\nSDL_mixer Error: " + Mix_GetError();
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
