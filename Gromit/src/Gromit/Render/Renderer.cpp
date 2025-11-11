#include "Renderer.h"
#include "../RenderAPIs/OpenGL/OpenGL_RenderAPI.h"
#include "RenderCommands.h"
#include "Math/Math.h"
#include "AssetManagement/AssetManager.h"

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

	void Renderer::OnUpdate(const SceneInstance& sceneInstance)
	{
		// begin scene
		//tempo

		Window* window = Context::SharedContext->GetWindows()[0];
		window->Activate();



		for (const auto& entity : sceneInstance.Entities)
		{
			auto iterator = tempRenderList.find(entity->InstanceID);
			if (iterator == tempRenderList.end())
			{
				MeshRendererComponentInstance* meshComponent = entity->GetComponent<MeshRendererComponentInstance>(ComponentType::MeshRenderer);
				tempRenderList.emplace(entity->InstanceID, std::move( RenderCommands::CreateRenderObject(*meshComponent))); //maybe have transform here? unsure
			}
		}

		window->PreUpdate();
		for (const auto& entity : sceneInstance.Entities)
		{
			TransformComponentInstance* transform = entity->GetComponent<TransformComponentInstance>(ComponentType::Transform);
			RenderCommands::DrawRenderObject(*tempRenderList[entity->InstanceID].get(), *transform, camera);
		}
		window->PostUpdate();



		//end scene
		update += 0.0005f;
		//tempRenderList.clear(); //to test
	}
}