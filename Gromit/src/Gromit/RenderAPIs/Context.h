#pragma once
#include "../Core.h"

namespace Gromit 
{
	class Context
	{
	public: 
		virtual void Init() = 0;
		virtual void Activate() = 0;
		virtual void SwapBuffers() = 0;
	};
}