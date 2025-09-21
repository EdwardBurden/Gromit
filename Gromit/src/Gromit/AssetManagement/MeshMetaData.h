#pragma once
#include "AssetManagement/MetaData.h"

#include <json.hpp>

namespace Gromit
{
	struct MeshMetaData : public MetaData
	{
	public:


		std::string m_assetPath;
		int m_importSetting;

		MeshMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, data)
		{
			data.at("importSetting").get_to(m_importSetting);
			m_assetPath = assetPath + m_path;
		}
	};
}