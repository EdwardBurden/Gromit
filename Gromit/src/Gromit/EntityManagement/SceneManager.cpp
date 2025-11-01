#include "SceneManager.h"
#include "../AssetManagement/Scene/SceneAsset.h"
#include "../AssetManagement/Entity/EntityAsset.h"
#include <AssetManagement/Entity/TransformAsset.h>
#include <AssetManagement/Entity/MeshRendererAsset.h>

namespace Gromit
{
	void UnLoadEntity(EntityInstance& entity);
	SceneInstance* SceneManager::m_activeScene;

	void SceneManager::OnStartUp()
	{

	}

	void SceneManager::OnShutDown()
	{

	}


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

	void MeshRendererComponentInstance::ApplyProperty(const std::string& name, const ComponentProperty& value)
	{
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		if (name == "mesh" && std::holds_alternative<int>(value))
		{
			//Should unload here if alreayd set
			mesh = assetManager->LoadAsset<MeshAsset>(std::get<int>(value)); //todo make assetmanegr use shared pointer so dont have ot worry baout unloading 
			return;
		}

		if (name == "material" && std::holds_alternative<int>(value))
		{
			//Should unload here if alreayd set
			material = assetManager->LoadAsset<MaterialAsset>(std::get<int>(value)); //todo make assetmanegr use shared pointer so dont have ot worry baout unloading 
			return;
		}

	}

	void SceneManager::UnLoadScene(int guid)
	{
		for (auto& entity : m_activeScene->Entities)
		{
			UnLoadEntity(*entity);
			delete entity;
		}
		ServiceLocator::GetService<AssetManager>()->UnLoadAsset(guid);

		delete m_activeScene;
		//get entites in scene.. call unload on them, should unload there components, dependancies etc.
			//unload form assetmanager to 
	}

	void SceneManager::LoadScene(int guid)
	{
		//int guid = 5;
		auto sceneAsset = ServiceLocator::GetService<AssetManager>()->LoadAsset<SceneAsset>(guid);
		m_activeScene = new SceneInstance();
		m_activeScene->Entities.clear();
		for (auto& entity : sceneAsset->GetEntities())
		{
			// TODO OPTOMISE BY FINDING ANY OBJECT IN THE SCENE WITH SAME GUID AND MAKING COPY ? 
			const auto& entityInstance = LoadEntity(*entity);	// go to load method
			m_activeScene->Entities.push_back(entityInstance);
		}
		//}
		//go to the assetmanager, find and load the scene raw asset. metadata already loaded assume
		//gets the scene and loop through each entity required,
		//		Load each entity and apply overrides to entityinstance

	}

	void UnLoadEntity(EntityInstance& entity)
	{
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		for (auto& comp : entity.Components)
		{
			switch (comp.first)
			{
			case ComponentType::Transform:
			{
				break;
			}

			case ComponentType::MeshRenderer:
			{
				auto meshInasstance = static_cast<MeshRendererComponentInstance*>(comp.second.get());
				int meshID = meshInasstance->mesh->GetGuid();
				meshInasstance->mesh.reset();
				assetManager->UnLoadAsset(meshID);

				int materialID = meshInasstance->material->GetGuid();
				meshInasstance->material.reset();
				assetManager->UnLoadAsset(materialID);
		
				//meshInasstance->mesh
				break;
			}
			default:
				break;
			}
		}



		//unload each component first then
		entity.AssetRef.reset();
		assetManager->UnLoadAsset(entity.GuiID);

	}

	EntityInstance* SceneManager::LoadEntity(const EntityReference& entityRef)
	{
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		EntityInstance* entity = new EntityInstance();
		entity->GuiID = entityRef.Guid;
		entity->InstanceID = entityRef.Instance;
		entity->Components.clear();
		entity->AssetRef = assetManager->LoadAsset<EntityAsset>(entityRef.Guid);
		for (auto& [key, component] : entity->AssetRef->GetComponents())
		{
			switch (component.get()->GetComponentType())
			{
			case ComponentType::Transform:
			{
				std::unique_ptr<TransformComponentInstance> transformComponentInstance = std::make_unique<TransformComponentInstance>();
				const auto& transformAsset = static_cast<TransformAsset*>(component.get());
				transformComponentInstance->m_position = transformAsset->m_position;
				transformComponentInstance->m_rotation = transformAsset->m_rotation;
				transformComponentInstance->ComponentID = transformAsset->GetID();
				transformComponentInstance->ComponentType = transformAsset->GetComponentType();

				const auto& overrides = entityRef.GetOverrides();
				auto iterator = overrides.find(key);
				if (iterator != entityRef.Overrides.end())
				{
					for (const auto& [overridepropertyName, overrideproperty] : iterator->second->Properties)
					{
						transformComponentInstance->ApplyProperty(overridepropertyName, overrideproperty);
					}
				}
				entity->Components.emplace(transformComponentInstance->ComponentType, std::move(transformComponentInstance));
				break;
			}
			case ComponentType::MeshRenderer:
			{
				std::unique_ptr<MeshRendererComponentInstance> meshComponentInstance = std::make_unique<MeshRendererComponentInstance>();
				const auto& meshAsset = static_cast<MeshRendererAsset*>(component.get());
				meshComponentInstance->mesh = assetManager->LoadAsset<MeshAsset>(meshAsset->m_mesh);
				meshComponentInstance->material = assetManager->LoadAsset<MaterialAsset>(meshAsset->m_material);
				meshComponentInstance->ComponentID = meshAsset->GetID();
				meshComponentInstance->ComponentType = meshAsset->GetComponentType();


				const auto& overrides = entityRef.GetOverrides();
				auto iterator = overrides.find(key);
				if (iterator != entityRef.Overrides.end())
				{
					for (const auto& [overridepropertyName, overrideproperty] : iterator->second->Properties)
					{
						meshComponentInstance->ApplyProperty(overridepropertyName, overrideproperty);
					}
				}
				entity->Components.emplace(meshComponentInstance->ComponentType, std::move(meshComponentInstance));
				break;
			}
			default:
				break;
			}

		}


		//go to the assetmanager, find and load the entity raw asset.metadata already loaded assume
		// Spawn into the world, add to world registry
		return entity;
	}

}