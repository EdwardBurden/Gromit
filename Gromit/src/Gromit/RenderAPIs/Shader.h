#pragma once
#include "../Core.h"

namespace Gromit 
{
	class GROMIT_API Shader
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	private:

	};
}