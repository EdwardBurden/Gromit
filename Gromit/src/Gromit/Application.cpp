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

		Context::SharedContext = Renderer::GetAPI()->CreateContext(); //temp
		camera = new Camera(90, 1);
		auto w = Gromit::ServiceLocator::GetService<Gromit::WindowManager>();
		w->CreateWindow(100, 100, 400, 400, "DLL Test1");
		w->CreateWindow(100, 100, 400, 400, "DLL Test2");
		test = 	RenderCommands::CreateRenderObject(Context::SharedContext); //would pass in mesh and shaer assets here
	}

	void Application::Run()
	{

		RenderCommands::DrawRenderObject(test, camera);

		ServiceLocator::GetService<WindowManager>()->OnUpdate();
		ServiceLocator::GetService<EventSystem>()->OnUpdate();
		//ServiceLocator::GetService<Renderer>()->OnUpdate();
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