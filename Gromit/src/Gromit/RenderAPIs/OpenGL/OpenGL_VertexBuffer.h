#pragma once
#include "../VertexBuffer.h"

namespace Gromit::OpenGL
{
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	public:
		OpenGL_VertexBuffer(float* vertices, uint32_t size);
		~OpenGL_VertexBuffer();
		void Bind() override;
		void Unbind() override;

	private:
		unsigned int VertexBufferId;
	};
}