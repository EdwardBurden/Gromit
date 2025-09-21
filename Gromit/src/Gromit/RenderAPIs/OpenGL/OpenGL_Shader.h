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
		unsigned int ShaderProgramId; //public get

	public:
		OpenGL_Shader(ShaderAsset* vert);
		~OpenGL_Shader();
	private:
		void Construct(char vertexShader[]);
	};
}