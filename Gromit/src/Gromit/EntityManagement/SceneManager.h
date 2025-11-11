#pragma once
#include "Math/Math.h"
#include "Core.h"
#include "ServiceLocator.h"
#include "AssetManagement/Entity/EntityAsset.h"
#include "AssetManagement/Mesh/MeshAsset.h"
#include "AssetManagement/Material/MaterialAsset.h"
#include "AssetManagement/Scene/SceneAsset.h"
#include "AssetManagement/AssetManager.h"
#include "EntityManagement/ComponentInstance.h"
#include <memory>

namespace Gromit
{
	struct EntityInstance
	{
		int InstanceID;
		int GuiID;
		std::shared_ptr<EntityAsset> AssetRef;
		std::unordered_map<ComponentType, std::unique_ptr<ComponentInstance>> Components;

		static EntityInstance* Create(const EntityReference& entityRef);
		void Destroy();

		template<typename T>
		T* GetComponent(ComponentType type)
		{
			auto it = Components.find(type);
			if (it == Components.end())
				return nullptr;

			return dynamic_cast<T*>(it->second.get());
		}
	};

	struct SceneInstance
	{
		std::vector<EntityInstance*> Entities;
	};

	class GROMIT_API SceneManager : public IEngineService
	{
	public:
		void OnStartUp() override;
		void OnShutDown() override;
		void LoadScene(int guid);
		void UnLoadScene(int guid); 
		static SceneInstance* m_activeScene;
	};
}