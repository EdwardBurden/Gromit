#pragma once
#include "Application.h"

namespace Gromit {

  bool Application::m_running = true;

	void Application::StartUp() {
		Logging::Init();
		m_windowManager = WindowManager::CreateManager(); //todo have define wrap or use othe rway
		m_windowManager->Init();
		m_windowManager->CreateWindowGromit(100, 100, 400, 400, "DLL Test1");
		m_windowManager->CreateWindowGromit(500, 500, 400, 400, "DLL Test2");
		m_running = true;
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