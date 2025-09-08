#pragma once

#include "RenderAPIs/VertexArray.h"

namespace Gromit::OpenGL
{
	class OpenGL_VertexArray : public VertexArray
	{
	public:

		OpenGL_VertexArray();
		~OpenGL_VertexArray();
		void Bind() override;
		void Unbind() override;
		void SetVertexBuffer(VertexBuffer* vertexBuffer)override;
		void SetIndexBuffer(IndexBuffer* indexBuffer) override;
	private:
		unsigned int VertexArrayId;
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
	};


}