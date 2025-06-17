#pragma once
#include "Application.h"

namespace Gromit {

	//static bool DoSomethingWindow(WindowsEvent& event);  // Declaration
	static bool DoSomethingMouse(MouseEvent& event);  // Declaration

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::StartUp() {
		Logging::Init();
		m_windowManager = WindowManager::CreateManager(); //todo have define wrap or use othe rway
		m_windowManager->Init();
		m_windowManager->CreateWindowGromit(100, 100, 400, 400, "DLL Test1");
		m_windowManager->CreateWindowGromit(500, 500, 400, 400, "DLL Test2");
	}


	static bool DoSomethingMouse(MouseEvent& event) {
		return false;
	}

	void Application::Run() {
		Gromit::EventSystem::Get().PerFrame();
		while (true);
	}

	void Application::ShutDown() {
		Logging::Release();
		m_windowManager->Release();
	}

}