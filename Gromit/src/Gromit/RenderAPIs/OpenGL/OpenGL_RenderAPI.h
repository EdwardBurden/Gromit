#pragma once
#include "../RenderAPI.h"
#include "../../Logging/Logging.h"
#include "OpenGL_Window.h"
#include "OpenGL_Shader.h"

//tod wrap in defines
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Gromit {
	namespace OpenGL {
		class OpenGL_RenderAPI : public RenderAPI
		{
		public:
			void Temp() override;
			void SetGlobalContext() override;
			void InitWindows() override;
			void TerminateWindows() override;
			Window* CreateWindow(int x, int y, int width, int height, const char* title) override;
			Shader* CreateShader(std::string vertexPath, std::string fragmentPath) override;
			static inline GLFWwindow* SharedContext = nullptr;
			void Update() override;
		private:
			unsigned int m_vertexArray, m_indexBuffer, m_vertexbuffer; //temp
			Shader* m_tempShader;
		};
	}
}