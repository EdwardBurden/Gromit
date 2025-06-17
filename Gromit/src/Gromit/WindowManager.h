#pragma once
#include "Core.h"
#include "Window.h"

namespace Gromit {
	class GROMIT_API WindowManager //abstract
	{
	public:
		WindowManager() {}
		~WindowManager() {}
		virtual void Init() = 0;
		virtual void Release() = 0;
		virtual Window* CreateWindowGromit(int x, int y, int width, int height, const char* title) = 0;
		static WindowManager* CreateManager();
	private:

	};

	
}