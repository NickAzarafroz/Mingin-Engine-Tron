#pragma once
namespace dae
{
	using Sound_ID = unsigned short;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Play(const Sound_ID id, const float volume) = 0;
		virtual void Release() = 0;
	};
}