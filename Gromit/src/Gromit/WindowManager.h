#pragma once
#include "Core.h"
#include "Renderer/Renderer.h"

namespace Gromit {
	class GROMIT_API WindowManager
	{
	public:
		WindowManager() {}
		~WindowManager() {}
		void Init();
		void Release();
		Window* CreateWindow(int x, int y, int width, int height, const char* title);
		void UpdateWindows();
		int WindowsCount();
	protected:
		std::vector<Window*> m_windows;
	};


}