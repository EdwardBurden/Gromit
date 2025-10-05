#include "AssetManagement/Entity/EntityAsset.h"
#include "AssetManagement/AssetDatabase.h"

namespace Gromit
{
	TransformAsset::TransformAsset(int id, ComponentType type, nlohmann::json data) : ComponentAsset(id, type)
	{
		auto position = data["position"];
		position.at("x").get_to(m_position.x);
		position.at("y").get_to(m_position.y);
		position.at("z").get_to(m_position.z);

		auto rotation = data["rotation"];
		rotation.at("x").get_to(m_rotation.x);
		rotation.at("y").get_to(m_rotation.y);
		rotation.at("z").get_to(m_rotation.z);
	}

	MeshRendererAsset::MeshRendererAsset(int id, ComponentType type, nlohmann::json data) : ComponentAsset(id, type)
	{
		data.at("mesh").get_to(m_mesh);
		data.at("material").get_to(m_material);
	}

	const std::vector<AssetDependency>& MeshRendererAsset::GetDependencies() const
	{
		return
		{
			{ AssetType::Mesh, m_mesh },
			{ AssetType::Material, m_material }
		};
	}

	EntityMetaData::EntityMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, assetPath, data)
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
}