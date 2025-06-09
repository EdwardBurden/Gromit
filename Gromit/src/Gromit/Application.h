#pragma once
#include "Core.h"

namespace Gromit {

	class GROMIT_API Application {
	public:
		Application();
		virtual ~Application();
		virtual void StartUp();
		void Run();
		void ShutDown();
	private:
		//EventSystem* m_eventSystem = nullptr;
	};

	Application* CreateApplication();
}