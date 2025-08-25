#include "OpenGL_Shader.h"
#include <glad/glad.h>

namespace Gromit::OpenGL
{
	//todo make shaderprogram which takes list of shaderassets, and here only compile one shader
		OpenGL_Shader::OpenGL_Shader(const ShaderAsset& vert, const ShaderAsset& frag) 
		{
			ShaderProgramId = glCreateProgram();
			VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
			Construct(vert.source.c_str(), frag.source.c_str());
		}

		OpenGL_Shader::~OpenGL_Shader()
		{
			glDeleteShader(VertexShaderId); // may be okay doing this in construct tbh.
			glDeleteShader(FragmentShaderId);
			glDeleteProgram(ShaderProgramId);
		}

		void OpenGL_Shader::Bind()
		{
			glUseProgram(ShaderProgramId);
		}

		void OpenGL_Shader::Unbind()
		{
			glUseProgram(0);
		}

		void OpenGL_Shader::Construct(const char* vertexShader, const char* fragmentShader)
		{
			int  success;
			char infoLog[512];
			// Vertex Compile
			glShaderSource(VertexShaderId, 1, &vertexShader, NULL);
			glCompileShader(VertexShaderId);
			glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(VertexShaderId, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			//Fragment Compile
			glShaderSource(FragmentShaderId, 1, &fragmentShader, NULL);
			glCompileShader(FragmentShaderId);
			glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(FragmentShaderId, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			//Shader Compile
			glAttachShader(ShaderProgramId, VertexShaderId);
			glAttachShader(ShaderProgramId, FragmentShaderId);
			glLinkProgram(ShaderProgramId);
			glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &success);

			if (!success) {
				glGetProgramInfoLog(ShaderProgramId, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::linker::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

	//	}
	}
}