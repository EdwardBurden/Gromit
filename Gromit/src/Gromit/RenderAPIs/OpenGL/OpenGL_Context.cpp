#include "OpenGL_Context.h"

namespace Gromit {
	namespace OpenGL {
		OpenGL_Context::OpenGL_Context(GLFWwindow* window)
		{
			m_window = window;
		}

		void OpenGL_Context::Init()
		{
			glfwMakeContextCurrent(m_window);
		}

		void OpenGL_Context::Activate()
		{
			glfwMakeContextCurrent(m_window);
		}

		void OpenGL_Context::SwapBuffers()
		{
			glfwSwapBuffers(m_window);
		}

	}
}