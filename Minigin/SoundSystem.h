#pragma once
namespace dae
{
	using Sound_id = unsigned short;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const Sound_id id, const float volume) = 0;
	};
}