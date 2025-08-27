#pragma once

namespace Gromit
{
	class Texture
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}