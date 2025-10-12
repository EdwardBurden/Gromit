#include "AssetManagement/Scene/SceneAsset.h"
#include "AssetManagement/AssetDatabase.h"

namespace Gromit 
{

	SceneMetaData::SceneMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, assetPath, data)
	{
		m_entities.clear();
		auto entities = data["entities"];
		for (size_t i = 0; i < entities.size(); i++)
		{
			auto entity = entities[i];
			int instance = entity.at("instance");
			int guid = entity.at("guid");
			EntityReference* e = new EntityReference();
			m_entities[instance] = e;
		}


	}


	REGISTER_ASSET_HANDLER(SceneAssetHandler, AssetType::Scene, SceneAsset, SceneMetaData, 8);
}