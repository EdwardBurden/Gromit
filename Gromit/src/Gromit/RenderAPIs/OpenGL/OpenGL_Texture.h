#pragma once
#include "../../AssetManagement/TextureAsset.h"
#include "RenderAPIs/Texture.h"

namespace Gromit::OpenGL
{
	class OpenGL_Texture : public Texture
	{
	public:
		OpenGL_Texture(const TextureAsset& asset);
		~OpenGL_Texture();
		void Bind() override;
		void Unbind() override;

	private:
		unsigned int TextureId;
	};
}