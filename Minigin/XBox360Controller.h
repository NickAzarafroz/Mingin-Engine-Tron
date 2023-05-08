#pragma once
#include <Windows.h>
 
namespace dae
{
	class XBox360Controller final
	{
	public:
		enum class ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000
		};

		void Update();
		bool IsDownThisFrame(ControllerButton button) const;
		bool IsUpThisFrame(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		unsigned int GetControllerIndex();

		explicit XBox360Controller(unsigned int controllerIndex);
		~XBox360Controller();

	private:
		class XBox360ControllerImpl;
		XBox360ControllerImpl* pImpl;
	};
}


