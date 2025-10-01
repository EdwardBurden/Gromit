#include "SceneManager.h"


namespace Gromit
{
	std::unique_ptr<SceneInstance> SceneManager::LoadScene(std::string sceneName)
	{
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
}