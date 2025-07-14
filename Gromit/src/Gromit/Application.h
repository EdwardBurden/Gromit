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
		static bool IsRunning();
		virtual void StartUp();
		virtual void Run();
		virtual void ShutDown();
		static void Stop();
	protected:
		static bool m_isRunning;
		WindowManager* m_windowManager;
		Renderer* m_renderer;
		//EventSystem* m_eventSystem = nullptr;
	};

	Application* CreateApplication();
}