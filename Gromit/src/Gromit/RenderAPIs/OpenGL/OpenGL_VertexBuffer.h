#pragma once
#include "../VertexBuffer.h"
#include "../BufferLayout.h"

namespace Gromit::OpenGL
{
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	public:
		OpenGL_VertexBuffer(float* vertices, uint32_t size);
		~OpenGL_VertexBuffer();
		void Bind() override;
		void Unbind() override;
		void SetLayout(BufferLayout* layout) override;
		BufferLayout* GetLayout() override;
	private:
		unsigned int VertexBufferId;
		BufferLayout* m_layout;
	};
}