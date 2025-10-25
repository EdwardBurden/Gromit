#pragma once
#include "Core.h"
#include "EntityManagement/SceneManager.h"
#include "EventSystem/EventSystem.h"
#include "Logging/Logging.h"
#include "WindowManager.h"
#include "Render/Render.h"
#include "ServiceLocator.h"
#include "FrameTime.h"

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
		//temp
		Context* testContext;
		RenderObject* testRender;
	};

	Application* CreateApplication();

}