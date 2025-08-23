#pragma once

namespace Gromit
{
	class IndexBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}