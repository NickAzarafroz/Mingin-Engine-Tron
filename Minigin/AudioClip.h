#pragma once
#include <string>
struct Mix_Chunk;

namespace dae
{
	class AudioClip
	{
    public:
        AudioClip() = default;
        ~AudioClip();

        AudioClip(const AudioClip& other) = delete;
        AudioClip(AudioClip&& other) = delete;
        AudioClip& operator=(const AudioClip& other) = delete;
        AudioClip& operator=(AudioClip&& other) = delete;

        bool IsLoaded() const;
        void Load(const std::string filePath);
        void SetVolume(float volume);
        void Play();

    private:
        Mix_Chunk* m_pMixChunk{};
	};
}


