#pragma once
#include <string>
struct Mix_Chunk;

namespace dae
{
	class AudioClip
	{
    public:
        AudioClip();
        ~AudioClip();

        bool IsLoaded() const;
        void Load(unsigned short id);
        void SetVolume(float volume);
        void Play();

    private:
        std::string m_FilePath;
        Mix_Chunk* m_pMixChunk{};
	};
}


