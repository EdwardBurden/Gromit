#include "SceneManager.h"
#include "../AssetManagement/Scene/SceneAsset.h"
#include "../AssetManagement/Entity/EntityAsset.h"
#include <AssetManagement/Entity/TransformAsset.h>
#include <AssetManagement/Entity/MeshRendererAsset.h>

namespace Gromit
{
	SceneInstance* SceneManager::m_activeScene;

	void SceneManager::OnStartUp()
	{

	}

	void SceneManager::OnShutDown()
	{

	}

	void SceneManager::UnLoadScene(int guid)
	{
		for (auto& entity : m_activeScene->Entities)
		{
			entity->Destroy();
			delete entity;
		}
		ServiceLocator::GetService<AssetManager>()->UnLoadAsset(guid);
		delete m_activeScene;
	}

	void SceneManager::LoadScene(int guid)
	{
		auto sceneAsset = ServiceLocator::GetService<AssetManager>()->LoadAsset<SceneAsset>(guid);
		m_activeScene = new SceneInstance();
		m_activeScene->Entities.clear();
		for (auto& entity : sceneAsset->GetEntities())
		{
			const auto& entityInstance = EntityInstance::Create(*entity);
			m_activeScene->Entities.push_back(entityInstance);
		}
	}

	void EntityInstance::Destroy()
	{
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		for (auto& comp : Components)
		{
			switch (comp.first)
			{
			case ComponentType::Transform:
			{
				auto transformInstance = static_cast<TransformComponentInstance*>(comp.second.get());
				transformInstance->OnDestory();
				break;
			}
			case ComponentType::MeshRenderer:
			{
				auto meshInstance = static_cast<MeshRendererComponentInstance*>(comp.second.get());
				meshInstance->OnDestory();
				break;
			}
			default:
				break;
			}
		}
		Components.clear();
		AssetRef.reset();
		assetManager->UnLoadAsset(GuiID);
	}

	EntityInstance* EntityInstance::Create(const EntityReference& entityRef)
	{
		const auto& assetManager = ServiceLocator::GetService<AssetManager>();
		EntityInstance* entity = new EntityInstance();
		entity->GuiID = entityRef.Guid;
		entity->InstanceID = entityRef.Instance;
		entity->Components.clear();
		entity->AssetRef = assetManager->LoadAsset<EntityAsset>(entityRef.Guid);
		for (auto& [key, component] : entity->AssetRef->GetComponents())
		{
			ComponentType type = component.get()->GetComponentType();
			switch (type)
			{
			case ComponentType::Transform:
			{
				auto ptr = ComponentInstance::CreateComponentInstance<TransformComponentInstance>(key, component, entityRef);
				entity->Components.emplace(type, std::move(ptr));
				break;
			}
			case ComponentType::MeshRenderer:
			{
				auto ptr = ComponentInstance::CreateComponentInstance<MeshRendererComponentInstance>(key, component, entityRef);
				entity->Components.emplace(type, std::move(ptr));
				break;
			}
			default:
				break;
			}
		}
		return entity;
	}

}