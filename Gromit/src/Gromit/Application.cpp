#pragma once
#include "Application.h"

namespace Gromit {

	bool Application::IsRunning()
	{
		return m_isRunning;
	}

	bool Application::m_isRunning = true;

	void Application::StartUp()
	{

		Logging::Init();

		m_renderer = new Renderer();
		m_renderer->SetAPI(RenderAPIType::OpenGL);

		m_windowManager = new WindowManager();
		m_windowManager->Init();
		m_windowManager->CreateWindow(100, 100, 400, 400, "DLL Test1");
		m_windowManager->CreateWindow(500, 500, 400, 400, "DLL Test2");
		m_isRunning = true;

		m_assetManager = new AssetManager();
		m_assetManager->IdentifyAssets("assets");
	}

	void Application::Run()
	{
		//TODO use layer system Her
		//Window
		m_windowManager->UpdateWindows();
		if (m_windowManager->WindowsCount() ==0) {
			Application::Stop();
			return;
		}	
		//Events
		EventSystem::Get().PerFrame();

		//Renderer
		//m_renderer.Update()
	}

	void Application::ShutDown()
	{
		Logging::Release();
		m_windowManager->Release();
		delete m_windowManager;
	}

	void Application::Stop()
	{
		m_isRunning = false;
	}

}