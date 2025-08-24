#include "OpenGL_VertexArray.h"

#include <glad/glad.h>

namespace Gromit::OpenGL
{
	OpenGL_VertexArray::OpenGL_VertexArray()
	{
		glGenVertexArrays(1, &VertexArrayId);
	}

	OpenGL_VertexArray::~OpenGL_VertexArray()
	{
		glDeleteVertexArrays(1, &VertexArrayId);
	}

	void OpenGL_VertexArray::Bind()
	{
		glBindVertexArray(VertexArrayId);
	}

	void OpenGL_VertexArray::Unbind()
	{
		glBindVertexArray(NULL);
	}
	
	void OpenGL_VertexArray::SetVertexBuffer(VertexBuffer* vertexBuffer)
	{
		Bind();
		vertexBuffer->Bind();
		auto layout = vertexBuffer->GetLayout();
		layout->SetAttributes();
		m_vertexBuffer = vertexBuffer;
	}
	
	void OpenGL_VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		Bind();
		indexBuffer->Bind();
		m_indexBuffer = indexBuffer;
	}
}