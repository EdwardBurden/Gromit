#pragma once
#include "../Window.h"
#include "../Logging/Logging.h"

//tod wrap in defines
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Gromit 
{
	class Windows_Window : public Window
	{
	public:
		Windows_Window(int x, int y, int width, int height, const char* title);
		~Windows_Window() {}
		void UpdateWindow() override;
	private:
		GLFWwindow* m_window;
	};
}