#include "SceneManager.h"
#include "../AssetManagement/Scene/SceneAsset.h"
#include "../AssetManagement/Entity/EntityAsset.h"

namespace Gromit
{
	std::unique_ptr<SceneInstance> SceneManager::LoadScene(std::string sceneName)
	{
		//SceneAsset* asset = ServiceLocator::GetService<AssetManager>()->LoadAsset<SceneAsset>(sceneName);

		//for (size_t i = 0; i < asset.; i++)
		//{

		//}
		//go to the assetmanager, find and load the scene raw asset. metadata already loaded assume
		//gets the scene and loop through each entity required,
		//		Load each entity and apply overrides to entityinstance
		return std::unique_ptr<SceneInstance>();
	}
	std::unique_ptr<EntityInstance> SceneManager::LoadEntity(std::string entityName)
	{
		//go to the assetmanager, find and load the entity raw asset.metadata already loaded assume
		// Spawn into the world, add to world registry
		return std::unique_ptr<EntityInstance>();
	}

	EntityInstance* EntityInstance::CreateInstance(int guid)
	{
		//EntityAsset* asset = ServiceLocator::GetService<AssetManager>()->LoadAsset<EntityAsset>(guid);
	//	EntityInstance* instance = new EntityInstance(asset);
		return nullptr;
	}

	EntityInstance* EntityInstance::CreateInstance(std::string name)
	{
		return nullptr;
	}
	void EntityInstance::DeleteInstance(EntityInstance* instance)
	{
		//ServiceLocator::GetService<AssetManager>()->UnloadAsset<EntityAsset>(instance->m_asset);
		// do soem thing shere to flag its being destroyed, maybe have scenemanaanger clear it next frame instead.
		delete instance;

	}
}