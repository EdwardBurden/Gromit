#include "Renderer.h"
#include "../RenderAPIs/OpenGL/OpenGL_RenderAPI.h"

namespace Gromit
{

	 RenderAPI* Renderer::m_activeRender;

	void Renderer::OnStartUp()
	{
		SetAPI(RenderAPIType::OpenGL);
	}

	void Renderer::OnShutDown()
	{

	}

	void Renderer::SetAPI(RenderAPIType renderApiType)
	{
		//todo clean up existing
		switch (renderApiType)
		{
		case Gromit::RenderAPIType::OpenGL:
			m_activeRender = new OpenGL::OpenGL_RenderAPI();
			break;
		case Gromit::RenderAPIType::DiurectX:
			break;
		case Gromit::RenderAPIType::Vulkan:
			break;
		}
	}
}