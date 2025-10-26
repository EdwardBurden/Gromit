#include "OpenGL_Shader.h"
#include <glad/glad.h>

namespace Gromit::OpenGL
{
	//todo make shaderprogram which takes list of shaderassets, and here only compile one shader
	OpenGL_Shader::OpenGL_Shader(const std::shared_ptr<ShaderAsset>& shader)
	{
		GLenum type = NULL;
		switch (shader->GetShaderType())
		{
		case ShaderType::Vertex:
			type = GL_VERTEX_SHADER;
			break;
		case ShaderType::Fragment:
			type = GL_FRAGMENT_SHADER;
			break;
		default:
			break;
		}

		ShaderProgramId = glCreateShader(type);
		Construct(shader->GetSource()); //todo this will be handled in the material grphics class, using dependant metadata
	}

	OpenGL_Shader::~OpenGL_Shader()
	{
		glDeleteShader(ShaderProgramId); // may be okay doing this in construct tbh.
	}

	void OpenGL_Shader::Construct(const char vertexShader[])
	{
		int  success;
		char infoLog[512];
		// Vertex Compile
		glShaderSource(ShaderProgramId, 1, &vertexShader, NULL);
		glCompileShader(ShaderProgramId);
		glGetShaderiv(ShaderProgramId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ShaderProgramId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
}