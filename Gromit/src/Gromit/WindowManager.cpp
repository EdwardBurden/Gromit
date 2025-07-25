#include "WindowManager.h"

namespace Gromit
{
	void WindowManager::OnStartUp()
	{
		auto renderer = ServiceLocator::GetService<Renderer>();
		auto api = renderer->GetAPI();
		api->InitWindows();

		CreateWindow(100, 100, 400, 400, "DLL Test1");
		CreateWindow(500, 500, 400, 400, "DLL Test2");
	}

	void WindowManager::OnShutDown()
	{
		auto renderer = ServiceLocator::GetService<Renderer>();
		auto api = renderer->GetAPI();
		api->TerminateWindows();
	}

	bool WindowManager::OnUpdate() 
	{
		for (int i = m_windows.size() - 1; i >= 0; --i)
		{
			m_windows[i]->UpdateWindow();
			if (m_windows[i]->m_close) {
				delete m_windows[i];
				m_windows.erase(m_windows.begin() + i);
			}
		}

		if (WindowsCount() == 0)
		{
			Application::Stop();
			return true;
		}
		return false;
	}

	Window* WindowManager::CreateWindow(int x, int y, int width, int height, const char* title)
	{
		auto renderer = ServiceLocator::GetService<Renderer>();
		auto api = renderer->GetAPI();
		Window* w = api->CreateWindow(x, y, width, height, title);
		m_windows.push_back(w);
		return w;
	}

	int WindowManager::WindowsCount()
	{
		return m_windows.size();
	}
}