#include "WindowManager.h"

namespace Gromit {
	void WindowManager::Init()
	{
		auto api = Renderer::GetAPI();
		api->InitWindows();
	}

	void WindowManager::Release()
	{
		auto api = Renderer::GetAPI();
		api->TerminateWindows();
	}

	void WindowManager::UpdateWindows()
	{
		for (int i = m_windows.size() - 1; i >= 0; --i)
		{
			m_windows[i]->UpdateWindow();
			if (m_windows[i]->m_close) {
				delete m_windows[i];
				m_windows.erase(m_windows.begin() + i);
			}
		}
	}

	Window* WindowManager::CreateWindow(int x, int y, int width, int height, const char* title)
	{
		auto api = Renderer::GetAPI();
		Window* w = api->CreateWindow(x, y, width, height, title);
		m_windows.push_back(w);
		return w;
	}

	int WindowManager::WindowsCount()
	{
		return m_windows.size();
	}
}