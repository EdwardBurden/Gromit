#pragma once
#include "../IndexBuffer.h"

namespace Gromit::OpenGL
{
	class OpenGL_IndexBuffer : public IndexBuffer
	{
	public:
		OpenGL_IndexBuffer(uint32_t* indices, uint32_t size);
		~OpenGL_IndexBuffer();
		void Bind() override;
		void Unbind() override;
		 int Count() override;
	private:
		unsigned int IndexBufferId;
		int count;
	};
}