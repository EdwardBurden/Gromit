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
		ServiceLocator::StartUp();

		//temp load test
		ServiceLocator::GetService<AssetManager>()->LoadIdentifiedAsset();
		//

		//temp
				///////////////TEMP PART

		BufferLayout* layout = Renderer::GetAPI()->CreateBufferLayout(
			{
				{ShaderDataType::Float3 , "position"},
				{ShaderDataType::Float3 , "normal"},
				{ShaderDataType::Float2 , "texCoords"}
			});
		const auto& manager = ServiceLocator::GetService<AssetManager>();
		MeshAsset* mesh = manager->GetAsset<MeshAsset>(32422333);
		ShaderAsset* vert = manager->GetAsset<ShaderAsset>(545);
		ShaderAsset* frag = manager->GetAsset<ShaderAsset>(123434);
		TextureAsset* smileTextureAsset = manager->GetAsset<TextureAsset>(345455675675);
		//////////////


		Context::SharedContext = Renderer::GetAPI()->CreateContext(); //temp
		auto w = Gromit::ServiceLocator::GetService<Gromit::WindowManager>();
		w->CreateWindow(100, 100, 400, 400, "DLL Test1");
		//w->CreateWindow(100, 100, 400, 400, "DLL Test2");
		testRender = RenderCommands::CreateRenderObject(Context::SharedContext, smileTextureAsset, vert, frag, mesh, layout); //would pass in mesh and shaer assets here
	}

	void Application::Run()
	{
		auto renderer = ServiceLocator::GetService<Renderer>();
		renderer->AddDrawObject(testRender);
		ServiceLocator::GetService<WindowManager>()->OnUpdate();
		ServiceLocator::GetService<EventSystem>()->OnUpdate();
		ServiceLocator::GetService<Renderer>()->OnUpdate();
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