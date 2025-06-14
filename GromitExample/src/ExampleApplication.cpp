#include "ExampleApplication.h"

Gromit::Application* Gromit::CreateApplication()
{
	return new ExampleApplication();
}


void ExampleApplication::StartUp()
{
	Application::StartUp();
	GL_INFO("App test");
	//Gromit::EventSystem& test = Gromit::EventSystem::Get();
	REG_EVENT(MouseClickEvent, this, DoSomethingMouse);
	TRIG_EVENT(MouseClickEvent, 0);
	//UREG_EVENT(MouseClickEvent, this);
}

 bool ExampleApplication::DoSomethingMouse(MouseClickEvent& event) {
	 GL_INFO("Call Back Fired for Mouse Event");
	return false;
	UREG_EVENT(MouseClickEvent, this);
}