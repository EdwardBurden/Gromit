#pragma once
#include "Math/Math.h"

namespace Gromit
{
	class Material
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetUniform(std::string name, glm::mat4 matrix) = 0;
	};
}