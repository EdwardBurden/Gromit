#include "ExampleApplication.h"

Gromit::Application* Gromit::CreateApplication()
{
	return new ExampleApplication();
}


void ExampleApplication::StartUp()
{
	Application::StartUp();
	Gromit::Logging::GetLogger()->info("App test");
	//Gromit::EventSystem& test = Gromit::EventSystem::Get();
	REG_EVENT(MouseClickEvent, this, DoSomethingMouse);
	TRIG_EVENT(MouseClickEvent, 0);
	//UREG_EVENT(MouseClickEvent, this);
}

 bool ExampleApplication::DoSomethingMouse(MouseClickEvent& event) {
	return false;
	//UREG_EVENT(MouseClickEvent, this); //todo add pending event list for this to work properly
}