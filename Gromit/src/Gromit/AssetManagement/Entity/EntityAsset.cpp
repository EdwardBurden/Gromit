#include "AssetManagement/Entity/EntityAsset.h"
#include "AssetManagement/Entity/TransformAsset.h"
#include "AssetManagement/Entity/MeshRendererAsset.h"
#include "AssetManagement/AssetDatabase.h"

namespace Gromit
{
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
				std::unique_ptr<TransformAsset> asset = std::make_unique<TransformAsset>(id, type, component);
				for (auto& dep : asset->GetDependencies())
				{
					AddDependency(dep.type, dep.guid);
				}
				m_components[id] = (std::move(asset));
				break;
			}
			case ComponentType::MeshRenderer:
			{
				std::unique_ptr<MeshRendererAsset> asset = std::make_unique<MeshRendererAsset>(id, type, component);
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
	REGISTER_ASSET_HANDLER(EntityAssetHandler, AssetType::Entity, EntityAsset, EntityMetaData, 8);
}