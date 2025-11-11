#pragma once

#include "RenderAPIs/BufferLayout.h"
#include "RenderAPIs/OpenGL/OpenGL.h"

namespace Gromit::OpenGL
{
	class OpenGL_BufferLayout : public BufferLayout
	{
	public:
		OpenGL_BufferLayout(const std::vector<BufferLayoutElement>& init) : m_data(init)
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