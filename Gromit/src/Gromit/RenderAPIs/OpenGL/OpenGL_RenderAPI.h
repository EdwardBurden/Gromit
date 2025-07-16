#pragma once
#include "../RenderAPI.h"
#include "../../Logging/Logging.h"
#include "OpenGL_Window.h"

//tod wrap in defines
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Gromit {
	namespace OpenGL {
		class OpenGL_RenderAPI : public RenderAPI
		{
			void InitWindows() override;
			void TerminateWindows() override;
			Window* CreateWindow(int x, int y, int width, int height, const char* title) override;

			void Update() override;
		};
	}
}