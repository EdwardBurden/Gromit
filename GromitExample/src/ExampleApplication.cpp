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
	//Gromit::EventSystem& test = Gromit::EventSystem::Get();
	REG_EVENT(Gromit::MouseClickEvent, this, DoSomethingMouse);
	REG_EVENT(Gromit::WindowsResizeEvent, this, DoSomethingWindow);
	//TRIG_EVENT(Gromit::MouseClickEvent, 0);
	//UREG_EVENT(MouseClickEvent, this);


	//RenderTest.
	// tell assetmanage to load the model, with dependencies
	//m_renderer->SubmitTest(Model1);
	//Load material using assetamanger
	//create camera at position
	//create square data here for now.
	// tell renderer to render the square + material at position





}

void ExampleApplication::Run()
{
	Application::Run();

	//m_renderer->DrawTest();
}


bool ExampleApplication::DoSomethingWindow(Gromit::WindowsResizeEvent& event) {

	GL_INFO("Width:{0}, Height:{1}", event.Width, event.Height);
	return false;
}


bool ExampleApplication::DoSomethingMouse(Gromit::MouseClickEvent& event) {
	GL_INFO("Call Back Fired for Mouse Event");
	m_windowManager->CreateWindow(900, 100, 300, 300, "EXE");
	return false;
	//UREG_EVENT(Gromit::MouseClickEvent, this);
}