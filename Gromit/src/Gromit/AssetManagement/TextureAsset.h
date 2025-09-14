#pragma once
#include "Asset.h"

#include <stb_image.h>
#include "AssetManagement/TextureMetaData.h"
namespace Gromit
{
	struct TextureAsset : public AssetNew
	{
		using MetaType = TextureMetaData;
		static constexpr size_t MAX_TEXTURE_SIZE = 2048; //temporary
		static constexpr size_t PoolCapacity = 50; //declared once

		int m_width;
		int m_height;
		int m_nrChannels;
		unsigned char m_data[MAX_TEXTURE_SIZE];

		TextureAsset(TextureMetaData* metaData)
		{
			stbi_set_flip_vertically_on_load(true); //add bool for this later
			unsigned char* ptr = stbi_load(metaData->m_assetPath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
			std::memcpy(m_data, ptr, std::strlen(reinterpret_cast<char*>(ptr)) + 1);
			//data = reinterpret_cast<char*>(loaded);
		}
	};
}