#include "OpenGL_IndexBuffer.h"

#include <glad/glad.h> 

namespace Gromit::OpenGL
{

	OpenGL_IndexBuffer::OpenGL_IndexBuffer(const std::vector<unsigned int>& indices)
	{
		glGenBuffers(1, &IndexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		count = indices.size();
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
	int OpenGL_IndexBuffer::Count()
	{
		return count;
	}
}