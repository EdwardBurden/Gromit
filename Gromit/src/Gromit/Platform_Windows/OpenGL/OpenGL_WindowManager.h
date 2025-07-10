#pragma once
#include "OpenGL_Window.h"
#include "../../WindowManager.h"

namespace Gromit
{
	namespace OpenGL {
		class OpenGL_WindowManager : public WindowManager
		{
		public:
			OpenGL_WindowManager() {}
			~OpenGL_WindowManager() {}
			void Init() override;
			void Release() override;
			void UpdateWindows() override;
			Window* CreateWindowGromit(int x, int y, int width, int height, const char* title) override;
			int WindowsCount()override;
		private:
			static void OnErrorCallback(int error, const char* description);
		};
	}
}