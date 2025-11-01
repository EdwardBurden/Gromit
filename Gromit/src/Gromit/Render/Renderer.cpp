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

		m_tempBuffer = Renderer::GetAPI()->CreateBufferLayout(
			{
				{ShaderDataType::Float3 , "position"},
				{ShaderDataType::Float3 , "normal"},
				{ShaderDataType::Float2 , "texCoords"}
			});
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

	void Renderer::OnUpdate(const SceneInstance& sceneInstance)
	{
		// begin scene
		for (const auto& entity : sceneInstance.Entities)
		{
			auto iterator = tempRenderList.find(entity->InstanceID);
			if (iterator == tempRenderList.end())
			{
				//add new renderobject
				const auto& base = entity->Components[ComponentType::MeshRenderer]; //TEMP assume one exists. //TODO make helper to get these later.
				const auto& mesh = static_cast<MeshRendererComponentInstance*>(base.get());
				//mesh.
				tempRenderList[entity->InstanceID] = RenderCommands::CreateRenderObject(mesh->material, mesh->mesh, m_tempBuffer);
			}
			RenderCommands::DrawRenderObject(tempRenderList[entity->InstanceID], camera);
		}
		//end scene
		update += 0.0005f;
		//tempRenderList.clear();
	}
}