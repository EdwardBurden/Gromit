#pragma once
#include "RenderAPIs/Window.h"

namespace Gromit 
{
	class Context
	{
	public: 
		static inline Context* SharedContext = nullptr;
		// needs list of windows set to this context
		virtual std::vector<Window*> GetWindows() = 0;
	};
}