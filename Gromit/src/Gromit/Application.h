#pragma once
#include "Core.h"
#include "EventSystem/EventSystem.h"
#include "Logging/Logging.h"
#include "WindowManager.h"
#include "AssetManagement/AssetManager.h"
#include "Renderer/Renderer.h"
#include "ServiceLocator.h"

namespace Gromit 
{
	class GROMIT_API Application
	{
	public:
		static bool IsRunning();
		virtual void StartUp();
		virtual void Run();
		virtual void ShutDown();
		static void Stop();
	protected:
		static bool m_isRunning;
	};

	Application* CreateApplication();
}