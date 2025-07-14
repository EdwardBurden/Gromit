#pragma once

#ifdef _WIN32

extern Gromit::Application* Gromit::CreateApplication();

int main(int argc, char* argv[]){
	auto app = Gromit::CreateApplication();
	app->StartUp();
	while (app->IsRunning)
	{
		app->Run(); // if we get the shutdown command then 
	}
	app->ShutDown();
	delete app;
}

#endif