#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>


#ifdef _WIN32

extern Gromit::Application* Gromit::CreateApplication();

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

	auto app = Gromit::CreateApplication();
	app->StartUp();
	while (app->IsRunning())
	{
		app->Run(); // if we get the shutdown command then 
	}
	app->ShutDown();
	delete app;
}

#endif