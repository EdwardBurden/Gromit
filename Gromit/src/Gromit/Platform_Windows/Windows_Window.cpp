#include "Windows_Window.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Gromit {

	Windows_Window::Windows_Window(int x, int y, int width, int height, const char* title)
	{
		GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
		{
			GL_ERROR("Failed to create GLFW window");
			return;
		}
		glfwSetWindowPos(window, x, y);
		glfwMakeContextCurrent(window);

		int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (version != 1) {
			GL_ERROR("Failed to initialize GLAD");
			return;
		}
		m_x = x;
		m_y = y;
		m_height = height;
		m_width = width;
		GL_INFO("Window Created");
	}
}