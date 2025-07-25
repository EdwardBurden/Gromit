#pragma once
#include "Application.h"
#include <typeinfo>

namespace Gromit {

	bool Application::IsRunning()
	{
		return m_isRunning;
	}

	bool Application::m_isRunning = true;

	void Application::StartUp()
	{
		m_isRunning = true;
		ServiceLocator::RegisterService<Logging>();
		ServiceLocator::RegisterService<Renderer>();
		ServiceLocator::RegisterService<WindowManager>();
		ServiceLocator::RegisterService<AssetManager>();
		ServiceLocator::RegisterService<EventSystem>();


		//Logging* logPtr = ServiceLocator::GetService<Logging>();

		ServiceLocator::StartUp();
		//Logging::Init();

		//m_renderer = new Renderer();
		//const std::type_info typeID = typeid(m_renderer);
		//m_renderer->SetAPI(RenderAPIType::OpenGL);

		//m_windowManager = new WindowManager();
		//m_windowManager->Init();
		//auto assetManager =ServiceLocator::GetService<AssetManager>();
		//assetManager->IdentifyAssets("assets");

		//m_serviceLocator.StartUp();
	}

	void Application::Run()
	{
		//TODO use layer system Her
		//Window
		//m_windowManager->UpdateWindows();
		ServiceLocator::Update();
		//if (m_windowManager->WindowsCount() ==0) {
		//	Application::Stop();
		//	return;
		//}	
		//Events
		//EventSystem::Get().PerFrame();

		//Renderer
		//m_renderer.Update()
	}

	void Application::ShutDown()
	{
		ServiceLocator::ShutDown();
		//Logging::Release();
		//m_windowManager->Release();
		//delete m_windowManager;
		//todo remove from register here
	}

	void Application::Stop()
	{
		m_isRunning = false;
	}

}