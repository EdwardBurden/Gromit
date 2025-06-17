#include "Windows_WindowManager.h"

namespace Gromit {

	WindowManager* WindowManager::CreateManager()
	{
		return new Windows_WindowManager();
	}


	void Windows_WindowManager::Init()
	{
		auto result = glfwInit();
		if (result)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			GL_INFO("GLFW Init Success");
		}
		else
		{
			GL_ERROR("Failed to Init GLFW");
		}
		return;
	}

	void Windows_WindowManager::Release()
	{
		glfwTerminate();
		GL_INFO("GLFW Release Success");
	}

	Window* Windows_WindowManager::CreateWindowGromit(int x, int y, int width, int height, const char* title)
	{
		//todo have window register
		Window* w = new Windows_Window(x, y, width, height, title);
		return w;
	}

}