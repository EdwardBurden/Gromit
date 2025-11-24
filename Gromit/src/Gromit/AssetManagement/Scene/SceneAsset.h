#pragma once
#include "AssetManagement/Asset.h"
#include "AssetManagement/Entity/EntityAsset.h"
#include <variant>

namespace Gromit
{
	struct SceneEntityOverride
	{
		SceneEntityOverride() = default;
		SceneEntityOverride(int id, ComponentType type) : ComponentID(id), ComponentType(type) {}

		int ComponentID;
		ComponentType ComponentType;


		std::unordered_map<std::string, ComponentProperty> Properties; //Example, "position": {	"x": 1,	"y" : 2,	"z" : 23}
	};

	struct EntityReference
	{
		EntityReference(int guid, int instance) : Guid(guid), Instance(instance) {}
		int Guid;
		int Instance;
		const std::unordered_map<int, SceneEntityOverride>& GetOverrides() const { return Overrides; }
		std::unordered_map<int, SceneEntityOverride> Overrides; //component id
	};


	struct SceneMetaData : public MetaData
	{
	public:
		SceneMetaData(int guid, std::string assetPath, nlohmann::json data);
		~SceneMetaData() override;
		std::vector<EntityReference> m_entities;
	};

	struct SceneAsset : public Asset
	{
		SceneAsset(std::shared_ptr<SceneMetaData> metaData) : Asset(metaData) {}
		const std::vector<EntityReference> GetEntities() const { return  this->GetMeta<SceneMetaData>()->m_entities; }
	};
}