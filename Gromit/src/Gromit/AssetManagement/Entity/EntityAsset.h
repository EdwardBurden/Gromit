#pragma once
#include "AssetManagement/Asset.h"

namespace Gromit
{
	enum class ComponentType
	{
		Transform = 0,
		MeshRenderer = 1
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(ComponentType,
		{
			{ComponentType::Transform, "Transform"},
			{ComponentType::MeshRenderer , "MeshRenderer"}
		});

	struct ComponentAsset
	{
	public:
		ComponentAsset(int id, ComponentType type) : m_id(id), m_componentType(type) {}
		virtual ~ComponentAsset() = default;
		const int GetID() const { return m_id; }
		const virtual std::vector<AssetDependency>& GetDependencies() const { return {}; }
		int m_id;
		ComponentType m_componentType;
	};

	struct EntityMetaData : public MetaData
	{
	public:
		EntityMetaData(int guid, std::string assetPath, nlohmann::json data);
	private:
		std::unordered_map<int, std::unique_ptr<ComponentAsset>> m_components; //todo make better pointers
	};

	struct EntityAsset : public Asset
	{
		EntityAsset(EntityMetaData* metaData) : Asset(metaData)	{}
	};
}