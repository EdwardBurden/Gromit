#pragma once
#include "../IndexBuffer.h"

namespace Gromit::OpenGL
{
	class OpenGL_IndexBuffer : public IndexBuffer
	{
	public:
		OpenGL_IndexBuffer(const std::vector<unsigned int>& indices);
		~OpenGL_IndexBuffer();
		void Bind() override;
		void Unbind() override;
		 int Count() override;
	private:
		unsigned int IndexBufferId;
		int count;
	};
}