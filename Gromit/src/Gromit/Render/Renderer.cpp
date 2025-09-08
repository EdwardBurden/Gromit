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

	void Renderer::OnUpdate() 
	{
		DrawRenderObject(RenderCommands::test, camera, update);
		update += 0.0005f;
	}


	void Renderer::DrawRenderObject(RenderObject* obj, Camera* camera, float update)
	{
		int index = 0;
		for (auto window : obj->m_context->GetWindows())
		{
			window->PreUpdate();
			obj->m_shader->Bind();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, obj->m_position);
			model *= glm::rotate(model, update, glm::vec3(0.05f, 0.2f, 0.05f));
			obj->m_shader->SetUniform("modelViewProjection", camera->GetViewPrrojection() * model);
			obj->m_contextbaseVA[index]->Bind();
			Renderer::GetAPI()->DrawIndexes(obj->m_indexBuffer->Count());	//DRAW HERE
			obj->m_shader->Unbind();
			obj->m_contextbaseVA[index]->Unbind();
			window->PostUpdate();
			index++;
		}
	}
}