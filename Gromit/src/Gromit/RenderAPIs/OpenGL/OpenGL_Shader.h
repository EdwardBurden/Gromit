#pragma once
#include "RenderAPIs/Shader.h"
#include "../../AssetManagement/ShaderAsset.h"
#include "Math/Math.h"

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
		 void SetUniform(std::string name, glm::mat4 matrix) override;
	private:
		void Construct(const char* vertexPath, const char* fragmentPath);
	};
}