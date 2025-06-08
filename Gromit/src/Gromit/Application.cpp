#include "Application.h"
#include "EngineLog.h"

namespace Gromit {

	static bool DoSomething(Event& event);  // Declaration

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::StartUp() {
		Event* test1 = new Event();
		test1->eventType = EventType::WindowOpenEvent;

		Event* test2 = new Event();
		test2->eventType = EventType::WindowOpenEvent;


		EventSystem* ev = new EventSystem();
		ev->RegisterListener(EventType::WindowOpenEvent, this, DoSomething);
		ev->Trigger(*test1);
		ev->Trigger(*test2);

		ev->PerFrame(); //update


		ev->UnregisterListener(EventType::WindowOpenEvent, this);


		EngineLog* loger = new EngineLog();
		loger->LogName();
		while (true);
	}
	static bool DoSomething(Event& event) {
		return false;
	}
}