#pragma once
#include "Application.h"

namespace Gromit {

  bool Application::m_running = true;

	void Application::StartUp() {

		Logging::Init();

		m_renderer = new Renderer();
		m_renderer->SetAPI(RenderAPIType::OpenGL);

		m_windowManager = new WindowManager();
		m_windowManager->Init();
		m_windowManager->CreateWindow(100, 100, 400, 400, "DLL Test1");
		m_windowManager->CreateWindow(500, 500, 400, 400, "DLL Test2");
		m_running = true;

		AssetManager assetMan;
		assetMan.IdentifyAssets("assets");
		assetMan.LoadAsset(345455675675);

		//look in the asset folder, find and serilized files.
		// load the .json file and keep in memory deserilized
		// load testure when needed
		//
	}

	void Application::Run() {

		while (m_running)
		{
			m_windowManager->UpdateWindows();
			Gromit::EventSystem::Get().PerFrame();
			if (m_windowManager->WindowsCount() < 1) {
				Application::Stop();
			}
		}
	}

	void Application::ShutDown() {
		Logging::Release();
		m_windowManager->Release();
		delete m_windowManager;
	}

	void Application::Stop() {
		m_running = false;
	
	}

}