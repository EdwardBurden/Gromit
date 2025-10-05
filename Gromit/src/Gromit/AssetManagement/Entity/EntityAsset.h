#pragma once
#include "AssetManagement/Asset.h"
#include "Math/Math.h"

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

	struct TransformAsset : public ComponentAsset
	{
	public:
		TransformAsset(int id, ComponentType type, nlohmann::json data);
		glm::vec3 m_position; //may need to convert manually
		glm::vec3 m_rotation; //may need to convert manually
	};

	struct MeshRendererAsset : public ComponentAsset
	{
	public:
		MeshRendererAsset(int id, ComponentType type, nlohmann::json data);
		const std::vector<AssetDependency>& GetDependencies() const override;
		int m_mesh;
		int m_material;
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