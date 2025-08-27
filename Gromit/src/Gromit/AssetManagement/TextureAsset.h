#pragma once
#include "Asset.h"

#include <stb_image.h>

namespace Gromit
{
	enum class TextureFormat {
		RED = 0,
		RGB = 1,
		RGBA = 2
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(TextureFormat, { {TextureFormat::RED, "RED"} });

	struct TextureAsset : public Asset
	{
		int width;
		int height;
		int nrChannels;
		TextureFormat format;
		bool generateMipMaps;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextureAsset, guid, type, name, path, width, height, format, generateMipMaps);

		unsigned char* data;

		//maybe have load method here later
		void Load() override
		{
			stbi_set_flip_vertically_on_load(true); //add bool for this later
			data = stbi_load(assetPath.c_str(), &width, &height, &nrChannels, 0);
			//data = reinterpret_cast<char*>(loaded);
		}
	};
}