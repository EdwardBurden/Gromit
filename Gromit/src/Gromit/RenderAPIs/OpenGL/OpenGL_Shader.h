#pragma once

#include <string>
#include "../Shader.h"
#include "../../AssetManagement/ShaderAsset.h"

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
		OpenGL_Shader(const ShaderAsset& vert, const ShaderAsset& frag);
		~OpenGL_Shader();
		void Bind() override;
		void Unbind() override;
	private:
		void Construct(const char* vertexPath, const char* fragmentPath);
	};
}