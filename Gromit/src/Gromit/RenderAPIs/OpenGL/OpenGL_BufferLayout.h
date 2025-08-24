#pragma once

#include "../BufferLayout.h"
#include <glad/glad.h> 

namespace Gromit::OpenGL
{
	class OpenGL_BufferLayout : public BufferLayout
	{
	public:
		OpenGL_BufferLayout(std::initializer_list<Gromit::BufferLayoutElement> init) : m_data(init)
		{
			SetStride();
		}

		void SetStride() override;
		void SetAttributes() override;
		GLenum ShaderDataTypeToEnum(const Gromit::ShaderDataType& type);
		GLint ShaderDataTypeToComponentSize(const Gromit::ShaderDataType& type);
	private:
		std::vector<BufferLayoutElement> m_data;
		int m_stride;
	};
}