#include "Application.h"
#include "EngineLog.h"

namespace Gromit {

	Application::Application() {
	
	}

	Application::~Application() {

	}

	void Application::StartUp() {
		EngineLog* loger = new EngineLog();
		loger->LogName();
		while (true);
	}
}