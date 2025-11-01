#pragma once
#include "AssetManagement/Texture/TextureAsset.h"
#include "RenderAPIs/Texture.h"

namespace Gromit::OpenGL
{
	class OpenGL_Texture : public Texture
	{
	public:
		OpenGL_Texture(const std::shared_ptr<TextureAsset>& asset);
		~OpenGL_Texture();
		void Bind() override;
		void Unbind() override;
		unsigned int ConvertFormat(TextureFormat format);
	private:
		unsigned int TextureId;
	};
}