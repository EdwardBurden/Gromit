#include "OpenGL_BufferLayout.h"

namespace Gromit::OpenGL
{
	void OpenGL_BufferLayout::SetAttributes()
	{
		int offset = 0;
		for (size_t i = 0; i < m_data.size(); i++)
		{
			//data
			glEnableVertexAttribArray(i);
			const auto& type = m_data[i].m_shaderDataType;
			GLsizei size = (GLsizei)type;
			glVertexAttribPointer(i, ShaderDataTypeToComponentSize(type), ShaderDataTypeToEnum(type), GL_FALSE, m_stride, (void*)offset); //todo add normalise switch
			offset += size;
		}
	}

	GLenum OpenGL_BufferLayout::ShaderDataTypeToEnum(const ShaderDataType& type) 
	{
		switch (type)
		{
		case ShaderDataType::None:   return 0;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
			return 0;
		}
	}

	GLint  OpenGL_BufferLayout::ShaderDataTypeToComponentSize(const ShaderDataType& type) 
	{
		switch (type)
		{
		case ShaderDataType::None:   return 0;
		case ShaderDataType::Float2: return 2;
		case ShaderDataType::Float3: return 3;
		case ShaderDataType::Float4: return 4;
			return 0;
		}
	}

	void OpenGL_BufferLayout::SetStride()
	{
		m_stride = 0;
		for (size_t i = 0; i < m_data.size(); i++)
		{
			GLsizei size = (GLsizei)m_data[i].m_shaderDataType;
			m_stride += size;
		}
	}
}