#pragma once
#include "AssetManagement/MetaData.h"
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
		ComponentAsset(int id, ComponentType type) : m_id(id), m_componentType(type) {}
		virtual ~ComponentAsset() = default;
		virtual void SetOverride(nlohmann::json data) = 0;
		int GetID() const { return m_id; }
		virtual std::vector<AssetDependency> GetDependencies() const { return {}; }
	private:
		int m_id;
		ComponentType m_componentType;
	};

	struct TransformAsset : public ComponentAsset
	{
		glm::vec3 m_position; //may need to convert manually
		glm::vec3 m_rotation; //may need to convert manually

		TransformAsset(int id, ComponentType type, nlohmann::json data) : ComponentAsset(id, type)
		{

			auto position = data["position"];
			position.at("x").get_to(m_position.x);
			position.at("y").get_to(m_position.y);
			position.at("z").get_to(m_position.z);

			auto rotation = data["rotation"];
			rotation.at("x").get_to(m_rotation.x);
			rotation.at("y").get_to(m_rotation.y);
			rotation.at("z").get_to(m_rotation.z);
			//data.at("rotation").get_to(m_rotation);
		}
	};

	struct MeshRendererAsset : public ComponentAsset
	{
		int m_mesh;
		int m_material;

		MeshRendererAsset(int id, ComponentType type, nlohmann::json data) : ComponentAsset(id, type)
		{
			data.at("mesh").get_to(m_mesh);
			data.at("material").get_to(m_material);
		}

		std::vector<AssetDependency> GetDependencies() const
		{
			return {
				{ AssetType::Mesh, m_mesh },
				{ AssetType::Material, m_material }
			};
		}
	};

	struct EntityMetaData : public MetaData
	{
	public:
		EntityMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, data)
		{
			m_components.clear();

			auto components = data["components"];
			for (size_t i = 0; i < components.size(); i++)
			{
				auto component = components[i];
				int id = component.at("componentID");
				ComponentType type = component.at("componentType");

				switch (type)
				{
				case ComponentType::Transform:
				{
					std::unique_ptr<ComponentAsset> asset = std::make_unique<TransformAsset>(id, type, component);
					for (auto& dep : asset->GetDependencies())
					{
						AddDependency(dep.type, dep.guid);
					}
					m_components[id] = (std::move(asset));
					break;
				}
				case ComponentType::MeshRenderer:
				{
					std::unique_ptr<ComponentAsset> asset = std::make_unique<MeshRendererAsset>(id, type, component);
					for (auto& dep : asset->GetDependencies())
					{
						AddDependency(dep.type, dep.guid);
					}
					m_components[id] = (std::move(asset));
					break;
				}
				default:
					break;
				}
			}

		}

	private:
		std::unordered_map<int, std::unique_ptr<ComponentAsset>> m_components; //todo make better pointers
	};
}
