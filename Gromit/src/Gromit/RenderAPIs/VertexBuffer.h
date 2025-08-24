#pragma once
#include "BufferLayout.h"

namespace Gromit
{
	class VertexBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetLayout(BufferLayout* layout) = 0;
		virtual BufferLayout* GetLayout() = 0;
	};
}