#pragma once
#include "../Core.h"
#include "Window.h"


namespace Gromit {

	class GROMIT_API RenderAPI
	{
	public:
		virtual void Temp() = 0;
		virtual void SetGlobalContext() = 0;
		virtual void InitWindows() = 0;
		virtual void TerminateWindows() = 0;
		virtual Window* CreateWindow(int x, int y, int width, int height, const char* title) = 0;

		virtual void Update() = 0;
	};
}