#pragma once
#include "Application.h"
#include <typeinfo>

namespace Gromit
{
	bool Application::m_isRunning = true;

	bool Application::IsRunning()
	{
		return m_isRunning;
	}

	void Application::StartUp()
	{
		m_isRunning = true;
		ServiceLocator::RegisterService<Logging>();
		ServiceLocator::RegisterService<Renderer>();
		ServiceLocator::RegisterService<WindowManager>();
		ServiceLocator::RegisterService<AssetManager>();
		ServiceLocator::RegisterService<EventSystem>();
		ServiceLocator::RegisterService<SceneManager>();
		ServiceLocator::StartUp();

		//temp load test
		//ServiceLocator::GetService<AssetManager>()->LoadIdentifiedAsset();
		//

		//temp
				///////////////TEMP PART

	/*	BufferLayout* layout = Renderer::GetAPI()->CreateBufferLayout(
			{
				{ShaderDataType::Float3 , "position"},
				{ShaderDataType::Float3 , "normal"},
				{ShaderDataType::Float2 , "texCoords"}
			});
			*/
		//const auto& manager = ServiceLocator::GetService<AssetManager>();
		//MeshAsset* mesh = manager->LoadAsset<MeshAsset>(32422333);
		//MaterialAsset* material = manager->LoadAsset<MaterialAsset>(999);
		//ShaderAsset* frag = manager->LoadAsset<ShaderAsset>(123434);
	//	TextureAsset* smileTextureAsset = manager->LoadAsset<TextureAsset>(345455675675);
		//////////////
		//EntityAsset* test = manager->LoadAsset<EntityAsset>(1);
		// 











		Context::SharedContext = Renderer::GetAPI()->CreateContext(); //temp
		auto w = Gromit::ServiceLocator::GetService<Gromit::WindowManager>();
		w->CreateWindow(100, 100, 400, 400, "DLL Test1");
		//w->CreateWindow(100, 100, 400, 400, "DLL Test2");
		//testRender = RenderCommands::CreateRenderObject(Context::SharedContext, material, mesh, layout); //would pass in mesh and shaer assets here
	}

	void Application::Run()
	{
	//	auto renderer = ServiceLocator::GetService<Renderer>();
	//	renderer->AddDrawObject(testRender); //temp will be set from the scene/world manager

	//	FrameTime::SetDelta();
		//ServiceLocator::GetService<WindowManager>()->OnUpdate();
		//hack must fix
		if (!m_isRunning)
			return;
		ServiceLocator::GetService<EventSystem>()->OnUpdate();
		const auto& sceneManger = ServiceLocator::GetService<SceneManager>();
		ServiceLocator::GetService<Renderer>()->OnUpdate(sceneManger->m_activeScene);
		//ServiceLocator::Update();
	}

	void Application::ShutDown()
	{
		ServiceLocator::ShutDown();
	}

	void Application::Stop()
	{
		m_isRunning = false;
	}
}