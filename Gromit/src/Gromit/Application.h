#pragma once
#include "Core.h"
#include "EventSystem/EventSystem.h"
#include "Logging/Logging.h"
#include "WindowManager.h"

namespace Gromit {

	class GROMIT_API Application {
	public:
		Application();
		virtual ~Application();
		virtual void StartUp();
		void Run();
		void ShutDown();
	protected:
		WindowManager* m_windowManager;
		//EventSystem* m_eventSystem = nullptr;
	};

	Application* CreateApplication();
}