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
	REG_EVENT(WindowsResizeEvent, this, DoSomethingWindow);
	TRIG_EVENT(MouseClickEvent, 0);
	//UREG_EVENT(MouseClickEvent, this);

#ifdef _DEBUG
	GL_INFO("Debug build");
#else
	GL_INFO("Release build");
#endif
}


bool ExampleApplication::DoSomethingWindow(WindowsResizeEvent& event) {
  
	GL_INFO("Width:{0}, Height:{1}", event.Width, event.Height);
	return false;
}


 bool ExampleApplication::DoSomethingMouse(MouseClickEvent& event) {
	 GL_INFO("Call Back Fired for Mouse Event");
	 m_windowManager->CreateWindowGromit(900, 100, 300, 300, "EXE");

	return false;
	UREG_EVENT(MouseClickEvent, this);
}