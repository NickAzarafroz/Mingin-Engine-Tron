#pragma once
#include <string>
namespace dae
{
	using SoundFile = std::string;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Play(const SoundFile filePath, const float volume, int loop) = 0;
		virtual void Stop() = 0;
		virtual void Release() = 0;
	};
}