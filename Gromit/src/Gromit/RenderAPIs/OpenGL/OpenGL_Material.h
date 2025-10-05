#pragma once
#include "RenderAPIs/Material.h"
#include "AssetManagement/Material/MaterialAsset.h"
#include "AssetManagement/Shader/ShaderAsset.h"
#include "Math/Math.h""


namespace Gromit::OpenGL
{
	class OpenGL_Material : public Material
	{
	public:

	private:
		unsigned int ShaderProgramId;
	public:
		OpenGL_Material(MaterialAsset* materialAsset);
		~OpenGL_Material();
		void Bind() override;
		void Unbind() override;
		void SetUniform(std::string name, glm::mat4 matrix) override;
	private:
		void Construct(MaterialAsset* materialAsset);

		std::vector<int> shaders;
		std::vector<int> textures;
	};
}