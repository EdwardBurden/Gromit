#pragma once
#include "../WindowManager.h"
#include "Windows_Window.h"
#include "../Logging/Logging.h"
#pragma once 
#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Gromit
{
	class Windows_WindowManager : public WindowManager
	{
	public:
		Windows_WindowManager() {}
		~Windows_WindowManager() {}
		void Init() override;
		void Release() override;
		Window* CreateWindowGromit(int x, int y, int width, int height, const char* title) override;
	private:

	};
}