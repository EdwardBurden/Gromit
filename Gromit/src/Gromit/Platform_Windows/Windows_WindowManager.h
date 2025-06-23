#pragma once
#include "../WindowManager.h"
#include "Windows_Window.h"

namespace Gromit
{
	class Windows_WindowManager : public WindowManager
	{
	public:
		Windows_WindowManager() {}
		~Windows_WindowManager() {}
		void Init() override;
		void Release() override;
		void UpdateWindows() override;
		Window* CreateWindowGromit(int x, int y, int width, int height, const char* title) override;
		int WindowsCount()override;
	private:
		static void OnErrorCallback(int error, const char* description);
	};
}