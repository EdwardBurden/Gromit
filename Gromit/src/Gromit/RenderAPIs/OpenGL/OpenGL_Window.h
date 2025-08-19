#pragma once
#include "../Window.h"
#include "../../Logging/Logging.h"
#include "../../EventSystem/EventSystem.h"
#include "../../RenderAPIs/OpenGL/OpenGL_Context.h"
#include "OpenGL_RenderAPI.h"

//tod wrap in defines
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Gromit
{
	namespace OpenGL {
		class OpenGL_Window : public Window
		{
		public:
			OpenGL_Window(int x, int y, int width, int height, const char* title);
			~OpenGL_Window() {}
			void Activate() override;
			void PreUpdate() override;
			void PostUpdate() override;
			void Close();
		private:
			GLFWwindow* m_window;
		};
	}
}