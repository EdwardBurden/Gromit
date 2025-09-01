#pragma once
#include "../Core.h"
#include <glm/glm.hpp>
#include <string>

namespace Gromit 
{
	class Shader
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetUniform(std::string name, glm::mat4 matrix) = 0;
	private:

	};
}