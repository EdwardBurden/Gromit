#pragma once
#include "Application.h"
#include <typeinfo>

namespace Gromit
{
	bool Application::m_isRunning = true;

	bool Application::IsRunning()
	{
		return m_isRunning;
	}

	void Application::StartUp()
	{
		m_isRunning = true;
		ServiceLocator::RegisterService<Logging>();
		ServiceLocator::RegisterService<Renderer>();
		ServiceLocator::RegisterService<WindowManager>();
		ServiceLocator::RegisterService<AssetManager>();
		ServiceLocator::RegisterService<EventSystem>();
		ServiceLocator::StartUp();

		auto renderer = ServiceLocator::GetService<Renderer>();
		renderer->Temp();
		const auto& windows = ServiceLocator::GetService<WindowManager>();
		for (size_t i = 0; i < windows->WindowsCount(); i++)
		{
			windows->m_windows[i]->Activate();
			renderer->SetGlobalContext();
		}
	}

	void Application::Run()
	{
		const auto& windows = ServiceLocator::GetService<WindowManager>();
		const auto& renderer = ServiceLocator::GetService<Renderer>();
		for (size_t i = 0; i < windows->WindowsCount(); i++)
		{
			windows->m_windows[i]->PreUpdate();
			renderer->OnUpdate();
			windows->m_windows[i]->PostUpdate();
		}
		windows->OnUpdate();
		//ServiceLocator::GetService<Renderer>()->OnUpdate();


		//window/context start
		//render per window
		//window/context end
		
		//ServiceLocator::Update();
	}

	void Application::ShutDown()
	{
		ServiceLocator::ShutDown();
	}

	void Application::Stop()
	{
		m_isRunning = false;
	}
}