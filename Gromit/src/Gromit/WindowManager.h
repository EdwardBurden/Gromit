#pragma once
#include "Core.h"
#include "Renderer/Renderer.h"
#include "Application.h"

namespace Gromit 
{
	class GROMIT_API WindowManager : public IEngineService
	{
	public:
		WindowManager() 
		{
			std::cout << "WindowManager Constructor" << std::endl;
		}
		void Init();
		void Release();
		Window* CreateWindow(int x, int y, int width, int height, const char* title);
		int WindowsCount();

		void OnStartUp() override;
		void OnShutDown() override;
		bool OnUpdate() ;

	private:
		std::vector<Window*> m_windows;
	};
}