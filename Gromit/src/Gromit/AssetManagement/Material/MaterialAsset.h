#pragma once
#include "AssetManagement/Asset.h"

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
		MaterialAsset(std::shared_ptr<MaterialMetaData> metaData) : Asset(metaData) {}
		const std::vector<int>& GetShaderIds() const { return GetMeta<MaterialMetaData>()->m_shaderIds; }
		const std::vector<int>& GetTextureIds() const { return GetMeta<MaterialMetaData>()->m_textureIds; }
	};
}