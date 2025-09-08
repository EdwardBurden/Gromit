#pragma once

#include "RenderAPIs/Context.h"
#include "RenderAPIs/OpenGL/OpenGL_Window.h"

namespace Gromit::OpenGL
{
	class OpenGL_Context : public Context
	{
	public:
		 std::vector<Window*> GetWindows() override;
		 void AddWindow(OpenGL_Window* window);
		 OpenGL_Window* GetShared();

	private:
		std::vector<OpenGL_Window*> m_windows;
	};
}