#include "AssetManagement/Texture/TextureAsset.h"
#include "AssetManagement/AssetDatabase.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
namespace Gromit
{
	TextureMetaData::TextureMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, assetPath, data)
	{
		data.at("width").get_to(m_width);
		data.at("height").get_to(m_height);
		data.at("format").get_to(m_format);
		data.at("generateMipMaps").get_to(m_generateMipMaps);
	}


	TextureAsset::TextureAsset(std::shared_ptr<TextureMetaData> metaData) : Asset(metaData)
	{
		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load(metaData->GetAssetPath().c_str(), &m_width, &m_height, &m_nrChannels, 0); //todo channel from metadata
		if (!m_data)
			throw std::runtime_error("Failed to load texture: " + metaData->GetAssetPath());
	}


	REGISTER_ASSET_HANDLER(TextureAssetHandler, AssetType::Texture, TextureAsset, TextureMetaData, 8);
}