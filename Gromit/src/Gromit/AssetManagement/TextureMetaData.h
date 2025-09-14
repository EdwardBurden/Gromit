#pragma once
#include "AssetManagement/MetaData.h"

namespace Gromit
{
	enum class TextureFormat
	{
		RED = 0,
		RGB = 1,
		RGBA = 2
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(TextureFormat, { {TextureFormat::RED, "RED"} }); //TODO need to use this later

	struct TextureMetaData : public MetaData
	{
	public:
		static constexpr size_t PoolCapacity = 50; //declared once
		std::string m_assetPath;
		int m_width;
		int m_height;
		TextureFormat m_format;
		bool m_generateMipMaps;

		TextureMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, data)
		{
			data.at("width").get_to(m_width);
			data.at("height").get_to(m_height);
			data.at("format").get_to(m_format);
			data.at("generateMipMaps").get_to(m_generateMipMaps);
			m_assetPath = assetPath + m_path;
		}
	};

}