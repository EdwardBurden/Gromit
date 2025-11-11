#include "EntityManagement/ComponentInstance.h"
#include <AssetManagement/Entity/TransformAsset.h>
#include <AssetManagement/Entity/MeshRendererAsset.h>

namespace Gromit
{
	void TransformComponentInstance::ApplyProperty(const std::string& name, const ComponentProperty& value)
	{
		if (name == "position" && std::holds_alternative<glm::vec3>(value))
		{
			m_position = std::get<glm::vec3>(value);
			return;
		}

		if (name == "rotation" && std::holds_alternative<glm::vec3>(value))
		{
			m_rotation = std::get<glm::vec3>(value);
			return;
		}
	}

	void TransformComponentInstance::SetComponent(const std::unique_ptr<ComponentAsset>& compAsset)
	{
		const auto& transformAsset = static_cast<TransformAsset*>(compAsset.get());
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		m_position = transformAsset->m_position;
		m_rotation = transformAsset->m_rotation;
		ComponentID = transformAsset->GetID();
		ComponentType = transformAsset->GetComponentType();
	}

	void TransformComponentInstance::OnDestory()
	{
		// nothing to do

	}

	void MeshRendererComponentInstance::ApplyProperty(const std::string& name, const ComponentProperty& value)
	{
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		if (name == "mesh" && std::holds_alternative<int>(value))
		{
			mesh.reset();
			mesh = assetManager->LoadAsset<MeshAsset>(std::get<int>(value));
			return;
		}

		if (name == "material" && std::holds_alternative<int>(value))
		{
			material.reset();
			material = assetManager->LoadAsset<MaterialAsset>(std::get<int>(value));
			return;
		}
	}

	void MeshRendererComponentInstance::SetComponent(const std::unique_ptr<ComponentAsset>& compAsset)
	{
		const auto& meshAsset = static_cast<MeshRendererAsset*>(compAsset.get());
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		mesh = assetManager->LoadAsset<MeshAsset>(meshAsset->m_mesh);
		material = assetManager->LoadAsset<MaterialAsset>(meshAsset->m_material);
		ComponentID = meshAsset->GetID();
		ComponentType = meshAsset->GetComponentType();
	}

	void MeshRendererComponentInstance::OnDestory()
	{
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		int meshID = mesh->GetGuid();
		mesh.reset();
		assetManager->UnLoadAsset(meshID);

		int materialID = material->GetGuid();
		material.reset();
		assetManager->UnLoadAsset(materialID);
	}
}