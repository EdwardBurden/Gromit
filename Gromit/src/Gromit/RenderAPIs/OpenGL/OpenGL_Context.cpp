#include "OpenGL_Context.h"

namespace Gromit {
	namespace OpenGL {

		std::vector<Window*> OpenGL_Context::GetWindows() //todo redo maybe
		{
			std::vector<Window*> result;
			result.reserve(m_windows.size()); // avoid reallocations
			for (auto& win : m_windows) {
				result.push_back(win); // take address -> Window*
			}
			return result;
		}

		void OpenGL_Context::AddWindow(OpenGL_Window* window)
		{
			m_windows.push_back(window);
		}

		OpenGL_Window* OpenGL_Context::GetShared() 
		{
			if (m_windows.size() == 0)
			{
				return nullptr;
			}
			return m_windows[0];
		}

	}
}