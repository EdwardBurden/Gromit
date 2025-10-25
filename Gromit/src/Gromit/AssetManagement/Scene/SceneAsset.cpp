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
			EntityReference* e = new EntityReference(guid, instance);
			e->Overrides.clear();
			for (auto& overrideJson : entity["overrides"])
			{
				int componentID = overrideJson["componentID"];
				ComponentType componentType = overrideJson["componentType"];
				auto overrideObj = new SceneEntityOverride(componentID, componentType);

				for (auto& [key, value] : overrideJson.items())
				{
					if (value.is_object() && value.contains("x") && value.contains("y") && value.contains("z"))
					{
						glm::vec3 vec(
							value["x"].get<float>(),
							value["y"].get<float>(),
							value["z"].get<float>()
						);
						overrideObj->Properties[key] = vec;
					}
					else if (value.is_number_integer())
					{
						overrideObj->Properties[key] = value.get<int>();
					}
					else if (value.is_number_float())
					{
						overrideObj->Properties[key] = value.get<float>();
					}
					else if (value.is_boolean())
					{
						overrideObj->Properties[key] = value.get<bool>();
					}
					else if (value.is_string())
					{
						overrideObj->Properties[key] = value.get<std::string>();
					}

				}

				e->Overrides[componentID] = overrideObj;
			}
			m_entities.push_back(e);
		}
	}


	REGISTER_ASSET_HANDLER(SceneAssetHandler, AssetType::Scene, SceneAsset, SceneMetaData, 8);
}