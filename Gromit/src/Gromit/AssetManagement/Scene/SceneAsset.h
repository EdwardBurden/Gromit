#pragma once
#include "AssetManagement/Asset.h"
#include <variant>
#include "Math/Math.h"

namespace Gromit
{	
	using ComponentProperty = std::variant<int, float, bool, std::string, glm::vec3>;

	struct SceneEntityOverride
	{
		std::unordered_map<std::string, ComponentProperty> Properties; //Example, "position": {	"x": 1,	"y" : 2,	"z" : 23}
	};

	struct EntityReference 
	{
		int Guid;
		int Instance;
		std::vector<SceneEntityOverride*> Overrides;
	};


	struct SceneMetaData : public MetaData
	{
	public:
		SceneMetaData(int guid, std::string assetPath, nlohmann::json data);

	private:
		std::vector<EntityReference*> m_entities;
	};

	struct SceneAsset : public Asset
	{

	};
}