#include "OpenGL_WindowManager.h"

namespace Gromit {

	WindowManager* WindowManager::CreateManager()
	{
		return new OpenGL::OpenGL_WindowManager();
	}

	namespace OpenGL {
		void OpenGL_WindowManager::Init()
		{
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

		void OpenGL_WindowManager::Release()
		{
			//todo close and delete all windows
			glfwTerminate();
			GL_INFO("GLFW Release Success");
		}


		void OpenGL_WindowManager::UpdateWindows()
		{

			for (int i = m_windows.size() - 1; i >= 0; --i)
			{
				m_windows[i]->UpdateWindow();
				if (m_windows[i]->m_close) {
					delete m_windows[i];
					m_windows.erase(m_windows.begin() + i);
				}
			}

		}


		Window* OpenGL_WindowManager::CreateWindowGromit(int x, int y, int width, int height, const char* title)
		{
			Window* w = new OpenGL_Window(x, y, width, height, title);
			m_windows.push_back(w);
			return w;
		}

		int OpenGL_WindowManager::WindowsCount()
		{
			return m_windows.size();
		}

		void OpenGL_WindowManager::OnErrorCallback(int error, const char* description)
		{
			GL_ERROR(error + description);
		}

	}
}