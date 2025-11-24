#include "AssetManagement/Texture/TextureAsset.h"
#include "AssetManagement/AssetDatabase.h"
#include "Core/LinearAllocator.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
namespace Gromit
{
	extern LinearAllocator textureAllocator;

	struct LoadedTextureData
	{
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_nrChannels;
		char* m_data; // todo improve
	};

	TextureMetaData::TextureMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, assetPath, data)
	{
		data.at("width").get_to(m_width);
		data.at("height").get_to(m_height);
		//	data.at("channels").get_to(m_channels);
		data.at("format").get_to(m_format);
		m_channels = 3;
		data.at("generateMipMaps").get_to(m_generateMipMaps);
	}


	TextureAsset::TextureAsset(std::shared_ptr<TextureMetaData> metaData) : Asset(metaData)
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(metaData->GetAssetPath().c_str(), &m_width, &m_height, &m_nrChannels, 0); //todo channel from metadata
		uint32_t size = m_width * m_height * m_nrChannels;

		if (!data)
			throw std::runtime_error("Failed to load texture: " + metaData->GetAssetPath());
		m_data = (unsigned char*)textureAllocator.AllocateBytes(size, alignof(uint16_t));
		memcpy(m_data, data, size);
		stbi_image_free(data);
	}

	TextureAsset::~TextureAsset()
	{
		//uint32_t size = m_width * m_height * m_nrChannels;
	//	textureAllocator.Free(m_data, size);
	}

	//todo on destructor, unallocate textures


	REGISTER_ASSET_HANDLER(TextureAssetHandler, AssetType::Texture, TextureAsset, TextureMetaData, 8);
}