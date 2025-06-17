#pragma once
#include "../Window.h"
#include "../Logging/Logging.h"

namespace Gromit 
{
	class Windows_Window : public Window
	{
	public:
		Windows_Window(int x, int y, int width, int height, const char* title);
		~Windows_Window() {}

	private:

	};
}