#pragma once
#include "../Core.h"

namespace Gromit 
{
	class Shader
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	private:

	};
}