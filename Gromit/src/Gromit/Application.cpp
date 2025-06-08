#include "Application.h"
#include "EngineLog.h"

namespace Gromit {

	static bool DoSomethingWindow(WindowsEvent& event);  // Declaration
	static bool DoSomethingMouse(MouseEvent& event);  // Declaration

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::StartUp() {
	
		EventSystem* ev = new EventSystem();
		ev->RegisterListener<WindowsEvent>(EventType::WindowOpenEvent, this, DoSomethingWindow);
		ev->RegisterListener<MouseEvent>(EventType::LeftMousePressedEvent, this, DoSomethingMouse);
		ev->Trigger<WindowsEvent>(9854, EventType::WindowOpenEvent);
		ev->Trigger<MouseEvent>('c', EventType::LeftMousePressedEvent);

		ev->PerFrame(); //update


		ev->UnregisterListener(EventType::WindowOpenEvent, this);


		EngineLog* loger = new EngineLog();
		loger->LogName();
		while (true);
	}
	static bool DoSomethingWindow(WindowsEvent& event) {
		return false;
	}

	static bool DoSomethingMouse(MouseEvent& event) {
		return false;
	}
}