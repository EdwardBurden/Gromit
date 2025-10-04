#pragma once

namespace Gromit
{
	struct SceneInstance
	{

	};

	struct EntityInstance
	{
		int m_instanceID; // can use this to cache agaianst render objects so its not recreated every frame
	};


	class SceneManager
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