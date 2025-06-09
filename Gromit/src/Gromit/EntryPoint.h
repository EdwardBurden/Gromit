#pragma once

#ifdef _WIN32

extern Gromit::Application* Gromit::CreateApplication();

int main(int argc, char* argv[]){
	Gromit::Logging::Init();

	auto app = Gromit::CreateApplication();
	app->StartUp();
	app->Run(); // if we get the shutdown command then 
	app->ShutDown();
	delete app;
	Gromit::Logging::Release();
}

#endif