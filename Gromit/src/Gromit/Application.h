#pragma once
#include "Core.h"
#include "EventSystem/EventSystem.h"
#include "Logging/Logging.h"
#include "WindowManager.h"
#include "AssetManagement/AssetManager.h"
#include "Renderer/Renderer.h"

namespace Gromit {

	//todo make layer system with list
	//Logging
	//EventSystem
	//WindowManager
	//Assetmanager
	//Renderer


	class GROMIT_API Application {
	public:
		Application() {};
		virtual ~Application() {};
		virtual void StartUp();
		void Run();
		void ShutDown();
		static void Stop();
	protected:
		static bool m_running;
		WindowManager* m_windowManager;
		Renderer* m_renderer;
		//EventSystem* m_eventSystem = nullptr;
	};

	Application* CreateApplication();
}