#include "OpenGL_IndexBuffer.h"

#include <glad/glad.h> 

namespace Gromit::OpenGL
{

	OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t* indices, uint32_t size)
	{
		glGenBuffers(1, &IndexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}
	OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
	{
		glDeleteBuffers(1, &IndexBufferId);
	}
	void OpenGL_IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
	}
	void OpenGL_IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}
}