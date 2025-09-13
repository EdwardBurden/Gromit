#pragma once
#include "AssetManagement/MetaData.h"

#include <json.hpp>

namespace Gromit
{
	struct MeshMetaData : public MetaData
	{
	public:
		static constexpr size_t PoolCapacity = 50; //declared once

		int m_guid;
		std::string m_name;
		std::string m_path;
		std::string m_assetPath;
		int m_importSetting;

		MeshMetaData(int guid, std::string assetPath, nlohmann::json data) 
		{
			data.at("guid").get_to(m_guid);
			data.at("name").get_to(m_name);
			data.at("path").get_to(m_path);
			data.at("importSetting").get_to(m_importSetting);
			m_assetPath = assetPath + m_path;
		}
	};
}