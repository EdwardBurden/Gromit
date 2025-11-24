#pragma once
#include "RenderAPIs/Window.h"

namespace Gromit 
{
	class Context
	{
	public: 
		Context() = default;
		virtual ~Context() = default;
		// needs list of windows set to this context
		virtual std::vector<Window*> GetWindows() = 0;
	};
}