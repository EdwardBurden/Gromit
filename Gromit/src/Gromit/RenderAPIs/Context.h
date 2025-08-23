#pragma once
#include "../Core.h"

namespace Gromit 
{
	class GROMIT_API Context
	{
	public: 
		virtual void Init() = 0;
		virtual void Activate() = 0;
		virtual void SwapBuffers() = 0;
	};
}