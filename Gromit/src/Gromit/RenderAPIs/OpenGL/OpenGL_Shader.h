#pragma once

#include <string>
#include "../Shader.h"
namespace Gromit::OpenGL
{
	class OpenGL_Shader : public Shader
	{
	public:

	private:
		unsigned int ShaderProgramId;
		unsigned int VertexShaderId;
		unsigned int FragmentShaderId;

	public:
		OpenGL_Shader(std::string vertexPath, std::string fragmentPath);
		~OpenGL_Shader();
		void Bind() override;
		void Unbind() override;
	private:
		void Construct(const char* vertexPath, const char* fragmentPath);
	};
}