#pragma once
#include "../Context.h"
#include "../../Logging/Logging.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Gromit {
	namespace OpenGL {
		class OpenGL_Context : public Context
		{
		public:
			OpenGL_Context(GLFWwindow* m_window);
			void Init() override;
			void Activate() override;
			void SwapBuffers() override;

		private:
			GLFWwindow* m_window;
		};
	}
}