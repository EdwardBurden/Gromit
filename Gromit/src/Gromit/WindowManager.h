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
		virtual void UpdateWindows() = 0;
		virtual int WindowsCount() = 0;
	protected:
		std::vector<Window*> m_windows;
	};

	
}