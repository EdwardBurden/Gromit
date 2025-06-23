#pragma once
#include <Gromit.h>

class ExampleApplication : public Gromit::Application
{
public: 
	ExampleApplication() {}
	~ExampleApplication() {}
	 void StartUp() override;
private:
	bool DoSomethingMouse(MouseClickEvent& event);
	bool DoSomethingWindow(WindowsResizeEvent& event);
};