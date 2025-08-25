#pragma once
#include "../Window.h"
#include "../../Logging/Logging.h"
#include "../../EventSystem/EventSystem.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


namespace Gromit::OpenGL
{
	class OpenGL_Window : public Window
	{
	public:
		OpenGL_Window(int x, int y, int width, int height, const char* title, GLFWwindow* shared);
		~OpenGL_Window() {}
		void Activate() override;
		void PreUpdate() override;
		void PostUpdate() override;
		void Close();
	//private:
		GLFWwindow* m_window;
	};
}