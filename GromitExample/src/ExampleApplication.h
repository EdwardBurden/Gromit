#pragma once
#include <Gromit.h>

class ExampleApplication : public Gromit::Application
{
public: 
	 void StartUp() override;
	 void Run() override;
private:
	bool DoSomethingMouse(Gromit::MouseClickEvent& event);
	bool DoSomethingWindow(Gromit::WindowsResizeEvent& event);
};