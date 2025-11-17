#pragma once
#include "AssetManagement/Asset.h"

namespace Gromit
{
	enum class TextureFormat
	{
		RED = 0,
		RGB = 1,
		RGBA = 2
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(TextureFormat, { 
		{TextureFormat::RED, "RED"},
		{TextureFormat::RGB, "RGB"},
		{ TextureFormat::RGBA, "RGBA" }
		});

	struct TextureMetaData : public MetaData
	{
	public:
		int m_width;
		int m_height;
		TextureFormat m_format;
		bool m_generateMipMaps;

		TextureMetaData(int guid, std::string assetPath, nlohmann::json data);// : MetaData(guid, assetPath, data);
	};

	struct TextureAsset : public Asset
	{
		int m_width;
		int m_height;
		int m_nrChannels;
		unsigned char* m_data; // todo improve

		TextureAsset(std::shared_ptr<TextureMetaData> metaData);
	};
}