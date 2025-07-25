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
	}

	void Application::Run()
	{
		ServiceLocator::Update();
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