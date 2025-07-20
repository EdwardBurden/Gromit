#include "Renderer.h"

//OpenGL
#include "../RenderAPIs/OpenGL/OpenGL_RenderAPI.h"

namespace Gromit {

	RenderAPI* Renderer::m_activeRender;

	int Renderer::vbo = 0;

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
		default:
			break;
		}
	}


	RenderAPI* Renderer::GetAPI()
	{
		//Vertex v;
		//v.Position = glm::vec3(1, 1, 1);
		return m_activeRender;
	}

	void Renderer::Update()
	{
		m_activeRender->Update();
	}
}