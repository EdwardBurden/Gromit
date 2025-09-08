#include "OpenGL_VertexBuffer.h"

#include <glad/glad.h> 

namespace Gromit::OpenGL
{
	/*OpenGL_VertexBuffer::OpenGL_VertexBuffer(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &VertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	*/
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(const std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &VertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	}

	OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
	{
		glDeleteBuffers(1, &VertexBufferId);
	}

	void OpenGL_VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
	}
	void OpenGL_VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}
	void OpenGL_VertexBuffer::SetLayout(BufferLayout* layout)
	{
		m_layout = layout;
	}

	BufferLayout* OpenGL_VertexBuffer::GetLayout()
	{
		return m_layout;
	}
}
