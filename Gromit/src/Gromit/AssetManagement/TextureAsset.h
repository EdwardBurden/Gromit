#pragma once
#include "Asset.h"
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
		TextureFormat format;
		bool generateMipMaps;
	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextureAsset, guid, type, name, path, width, height, format, generateMipMaps)
	};
}