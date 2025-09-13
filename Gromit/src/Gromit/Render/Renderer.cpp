#include "Renderer.h"
#include "../RenderAPIs/OpenGL/OpenGL_RenderAPI.h"
#include "RenderCommands.h"

namespace Gromit
{

	RenderAPI* Renderer::m_activeRender;

	void Renderer::OnStartUp()
	{
		SetAPI(RenderAPIType::OpenGL);
		update = 0;
		camera = new Camera(90, 1);
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

	void Renderer::AddDrawObject(RenderObject* obj)
	{
		tempRenderList.push_back(obj);
	}

	void Renderer::OnUpdate()
	{
		// begin scene
		for (auto obj : tempRenderList)
		{
			RenderCommands::DrawRenderObject(obj, camera);
		}
		//end scene
		update += 0.0005f;
		tempRenderList.clear();
	}
}