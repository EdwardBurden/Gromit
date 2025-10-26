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
		const ComponentType GetComponentType() const { return m_componentType; }
		const virtual std::vector<AssetDependency> GetDependencies() const { return {}; }
	private:
		int m_id;
		ComponentType m_componentType;
	};

	struct EntityMetaData : public MetaData
	{
	public:
		EntityMetaData(int guid, std::string assetPath, nlohmann::json data);

		std::unordered_map<int, std::unique_ptr<ComponentAsset>> m_components; //todo make better pointers
	};

	struct EntityAsset : public Asset
	{
		EntityAsset(std::shared_ptr<EntityMetaData> metaData) : Asset(metaData) {}

		inline const std::unordered_map<int, std::unique_ptr<ComponentAsset>>& GetComponents() const { return this->GetMeta<EntityMetaData>()->m_components; }
	};
}