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

	Gromit::ServiceLocator::GetService<Gromit::AssetManager>()->IdentifyAssets("assets"); // would be core or example folders in future
	Gromit::ServiceLocator::GetService<Gromit::AssetManager>()->IdentifyAssets("pack 1");
	//TO Load our local Asset Pack 
	//Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->LoadScene(5); //-> will also load the asset,camera etc and handle rendering
	//Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->LoadScene(10);
	//Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->UnLoadScene(5);
	//Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->UnLoadScene(10);
}

void ExampleApplication::Run()
{
	Application::Run();
}

bool ExampleApplication::DoSomethingWindow(Gromit::WindowsResizeEvent& event)
{
	//Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->UnLoadScene(5);
	GL_INFO("Width:{0}, Height:{1}", event.Width, event.Height);
	return false;
}

bool ExampleApplication::DoSomethingMouse(Gromit::MouseClickEvent& event) 
{
	if (event.button == 0) 
	{
		Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->UnLoadScene(5);
	}
	if (event.button == 1)
	{
		Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->LoadScene(5);
	}
	GL_INFO("Call Back Fired for Mouse Event");
	//Gromit::ServiceLocator::GetService<Gromit::SceneManager>()->UnLoadScene(5);
	//auto w = Gromit::ServiceLocator::GetService<Gromit::WindowManager>(); //wrap in macro
	//w->CreateWindow(900, 100, 300, 300, "EXE");
	return false;
	//UREG_EVENT(Gromit::MouseClickEvent, this);
}