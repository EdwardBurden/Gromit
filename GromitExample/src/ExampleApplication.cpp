#include "ExampleApplication.h"

Gromit::Application* Gromit::CreateApplication()
{
	return new ExampleApplication();
}

static bool DoSomethingMouse(MouseEvent& event);  // Declaration

void ExampleApplication::StartUp()
{
	Application::StartUp();
	//Gromit::EventSystem& test = Gromit::EventSystem::Get();
	REG_EVENT(MouseEvent, EventType::LeftMousePressedEvent, this, DoSomethingMouse);
	TRIG_EVENT(MouseEvent, 'C', EventType::LeftMousePressedEvent);
}

static bool DoSomethingMouse(MouseEvent& event) {
	return false;
}