#pragma once
#include "Application.h"
#include "../Grom_pch.h"
namespace Gromit {

	//static bool DoSomethingWindow(WindowsEvent& event);  // Declaration
	static bool DoSomethingMouse(MouseEvent& event);  // Declaration

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::StartUp() {
		//Gromit::EngineLog::StartUp();
	//	GROMIT_INFO("Engine StartUp");
		//auto m_eventSystem = new EventSystem();
		//auto stat = m_eventSystem->s_eventSystem;
	//REG_EVENT(MouseEvent, EventType::LeftMousePressedEvent, this, DoSomethingMouse);
	//TRIG_EVENT(MouseEvent, 'C', EventType::LeftMousePressedEvent);	
	//m_eventSystem->RegisterListener<WindowsEvent>(EventType::WindowOpenEvent, this, DoSomethingWindow);
	//	m_eventSystem->RegisterListener<MouseEvent>(EventType::LeftMousePressedEvent, this, DoSomethingMouse);
		//m_eventSystem->Trigger<WindowsEvent>(9854, EventType::WindowOpenEvent);
		//m_eventSystem->Trigger<MouseEvent>('c', EventType::LeftMousePressedEvent);
	//Gromit::EventSystem::Get().PerFrame();
		//m_eventSystem->PerFrame(); //update


	//	m_eventSystem->UnregisterListener(EventType::WindowOpenEvent, this);
		
		//while (true);
	//	GROMIT_INFO("Engine Shutdown");
	//	Gromit::EngineLog::ShutDown();
	}
	/*static bool DoSomethingWindow(WindowsEvent& event) {
		return false;
	}
	*/
	static bool DoSomethingMouse(MouseEvent& event) {
		return false;
	}

	void Application::Run() {
		Gromit::EventSystem::Get().PerFrame();
		while (true);
	}

	void Application::ShutDown() {
		//Gromit::Logging::Release();
	}

}