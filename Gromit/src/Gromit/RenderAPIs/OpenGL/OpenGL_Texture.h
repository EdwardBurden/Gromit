#pragma once
#include <string>
#include "../../AssetManagement/TextureAsset.h"
#include "../Texture.h"

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