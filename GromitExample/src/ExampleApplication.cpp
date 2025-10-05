#include "ExampleApplication.h"

Gromit::Application* Gromit::CreateApplication()
{
	return new ExampleApplication();
}

void ExampleApplication::StartUp()
{

	Application::StartUp();

#ifdef _DEBUG
	GL_INFO("Debug build");
#else
	GL_INFO("Release build");
#endif
	GL_INFO("App test");
	REG_EVENT(Gromit::MouseClickEvent, this, DoSomethingMouse);
	REG_EVENT(Gromit::WindowsResizeEvent, this, DoSomethingWindow);

	Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->LoadScene("test"); //-> will also load the asset,camera etc and handle rendering
	//REG_EVENT(Gromit::KeyPress, this, Close/Open different scene);
}

void ExampleApplication::Run()
{
	Application::Run();
}

bool ExampleApplication::DoSomethingWindow(Gromit::WindowsResizeEvent& event)
{

	GL_INFO("Width:{0}, Height:{1}", event.Width, event.Height);
	return false;
}

bool ExampleApplication::DoSomethingMouse(Gromit::MouseClickEvent& event) 
{
	GL_INFO("Call Back Fired for Mouse Event");
	auto w = Gromit::ServiceLocator::GetService<Gromit::WindowManager>(); //wrap in macro
	w->CreateWindow(900, 100, 300, 300, "EXE");
	return false;
	//UREG_EVENT(Gromit::MouseClickEvent, this);
}