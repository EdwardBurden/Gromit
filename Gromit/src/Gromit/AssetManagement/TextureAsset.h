#pragma once
#include "Asset.h"

#include <stb_image.h>
#include "AssetManagement/TextureMetaData.h"
namespace Gromit
{
	struct TextureAsset : public Asset
	{
		using MetaType = TextureMetaData;

		int m_width;
		int m_height;
		int m_nrChannels;
		//std::unique_ptr<unsigned char[]> m_data; // heap for image data
		unsigned char* m_data; //to improve

		TextureAsset(TextureMetaData* metaData)
		{
			stbi_set_flip_vertically_on_load(true);

			m_data = stbi_load(metaData->m_assetPath.c_str(), &m_width, &m_height, &m_nrChannels, 0); //todo channel from metadata
			if (!m_data)
				throw std::runtime_error("Failed to load texture: " + metaData->m_assetPath);

			//size_t size = static_cast<size_t>(m_width) * m_height * 4;
			//m_data = std::make_unique<unsigned char[]>(size);
			//std::memcpy(m_data.get(), ptr, size);

				//stbi_image_free(m_data); // free stb’s buffer
		}
	};
}