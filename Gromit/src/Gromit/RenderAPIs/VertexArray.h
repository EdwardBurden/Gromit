#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Gromit
{
	class VertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;
	private:

	};
}