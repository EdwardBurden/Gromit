#pragma once
#include "RenderAPIs/IndexBuffer.h"

namespace Gromit::OpenGL
{
	class OpenGL_IndexBuffer : public IndexBuffer
	{
	public:
		OpenGL_IndexBuffer(const unsigned int* indices, unsigned int size);
		~OpenGL_IndexBuffer();
		void Bind() override;
		void Unbind() override;
		 int Count() override;
	private:
		unsigned int IndexBufferId;
		int count;
	};
}