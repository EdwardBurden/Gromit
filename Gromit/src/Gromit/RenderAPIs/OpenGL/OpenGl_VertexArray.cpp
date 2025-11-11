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
		//todo clean up index and vertex pointers
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
		m_vertexBuffer = vertexBuffer;
		Bind();
		m_vertexBuffer->Bind();
		auto layout = m_vertexBuffer->GetLayout();
		layout->SetAttributes();
		
	}
	
	void OpenGL_VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{	
		m_indexBuffer = indexBuffer;
		Bind();
		m_indexBuffer->Bind();
	
	}

	void OpenGL_VertexArray::Draw() 
	{
		glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, 0);
	};
}