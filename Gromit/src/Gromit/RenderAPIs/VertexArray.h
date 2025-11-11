#pragma once

#include "RenderAPIs/VertexBuffer.h"
#include "RenderAPIs/IndexBuffer.h"

namespace Gromit
{
	class VertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;
		virtual void Draw() = 0;
	private:

	};
}