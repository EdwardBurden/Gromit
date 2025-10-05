#pragma once
#include "AssetManagement/AssetManager.h" // only in cpp!
#include "Core.h"
#include "ServiceLocator.h"


namespace Gromit
{
	struct SceneInstance
	{

	};

	struct EntityInstance
	{
		int m_instanceID; // can use this to cache agaianst render objects so its not recreated every frame
		//EntityInstance(EntityAsset* entity) : m_asset(entity)
		//{
		
	//	}



		static EntityInstance* CreateInstance(int guid);
		static EntityInstance* CreateInstance(std::string name);
		static void DeleteInstance(EntityInstance* instance);

	private:
		//EntityAsset* m_asset; // shared pointer todo
	};


	class GROMIT_API SceneManager : public IEngineService
	{
	public:
		std::unique_ptr<SceneInstance> LoadScene(std::string sceneName); //Loads a scene at root(implied) and all entities required
		std::unique_ptr <EntityInstance> LoadEntity(std::string entityName);

		inline void Update() 
		{
		// call the renderer and pass through the list of entities to render.

		}

		static std::unique_ptr<SceneInstance> m_activeScene;
		static std::vector<std::unique_ptr <EntityInstance>> m_activeEntites;

	};
}