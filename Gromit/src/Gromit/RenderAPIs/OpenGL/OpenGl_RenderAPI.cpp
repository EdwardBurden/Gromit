#include "OpenGL_RenderAPI.h"

namespace Gromit {
	namespace OpenGL {

		void OnErrorCallback(int error, const char* description);

		void OpenGL_RenderAPI::InitWindows() {
			auto result = glfwInit();
			if (result)
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwSetErrorCallback(OnErrorCallback);
				GL_INFO("GLFW Init Success");
			}
			else
			{
				GL_ERROR("Failed to Init GLFW");
			}
			return;
		}

		void OpenGL_RenderAPI::TerminateWindows()
		{
			glfwTerminate();
			GL_INFO("GLFW Release Success");
		}

		Window* OpenGL_RenderAPI::CreateWindow(int x, int y, int width, int height, const char* title)
		{
			Window* w = new OpenGL_Window(x, y, width, height, title);
			return w;
		}


		void OnErrorCallback(int error, const char* description)
		{
			GL_ERROR(error + description);
		}

	}
}
