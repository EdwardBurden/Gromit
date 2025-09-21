#include "OpenGL_Material.h"
#include "ResourceRegistry.h"

#include <glad/glad.h>

namespace Gromit::OpenGL
{
	OpenGL_Material::OpenGL_Material(MaterialAsset* materialAsset)
	{
		ShaderProgramId = glCreateProgram();
		Construct(materialAsset);
	}

	OpenGL_Material::~OpenGL_Material()
	{
		glDeleteProgram(ShaderProgramId);
	}

	void OpenGL_Material::Bind()
	{
		for (size_t i = 0; i < textures.size(); i++)
		{
			auto texture = ResourceRegistry::Textures[textures[i]];
			texture->Bind();
		}



		glUseProgram(ShaderProgramId);

	}

	void OpenGL_Material::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGL_Material::SetUniform(std::string name, glm::mat4 matrix)
	{
		int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
		glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGL_Material::Construct(MaterialAsset* materialAsset)
	{
		//Shader Compile
		//materialAsset->
		int  success;
		char infoLog[512];
		//we will need the shaders here 
		 shaders = materialAsset->GetShaderIds();
		for (size_t i = 0; i < shaders.size(); i++)
		{
			auto shader = ResourceRegistry::Shaders[shaders[i]];
			glAttachShader(ShaderProgramId, shader->GetShaderId());
		}
		//	glAttachShader(ShaderProgramId, VertexShaderId);
		//	glAttachShader(ShaderProgramId, FragmentShaderId);
		glLinkProgram(ShaderProgramId);
		glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(ShaderProgramId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::linker::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		textures = materialAsset->GetTextureIds();


		//	}
	}
}