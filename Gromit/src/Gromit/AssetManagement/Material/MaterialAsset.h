#pragma once
#include "AssetManagement/Asset.h"
#include "AssetManagement/Texture/TextureAsset.h"
#include "AssetManagement/Shader/ShaderAsset.h"

namespace Gromit
{
	struct MaterialMetaData : public MetaData
	{
	public:
		MaterialMetaData(int guid, std::string assetPath, nlohmann::json data);
		std::vector<int> m_shaderIds;
		std::vector<int> m_textureIds;
	};

	struct MaterialAsset : public Asset
	{
	public:
		MaterialAsset(std::shared_ptr<MaterialMetaData> metaData);
		~MaterialAsset();
		const std::vector<int>& GetShaderIds() const { return GetMeta<MaterialMetaData>()->m_shaderIds; }
		const std::vector<int>& GetTextureIds() const { return GetMeta<MaterialMetaData>()->m_textureIds; }

		std::vector<std::shared_ptr<ShaderAsset>> m_shaders;
		std::vector<std::shared_ptr<TextureAsset>> m_textures;

	};
}