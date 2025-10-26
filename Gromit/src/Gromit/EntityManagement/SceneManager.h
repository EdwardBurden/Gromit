#pragma once
#include "Math/Math.h"
#include "Core.h"
#include "ServiceLocator.h"
#include "AssetManagement/Entity/EntityAsset.h"
#include "AssetManagement/Mesh/MeshAsset.h"
#include "AssetManagement/Material/MaterialAsset.h"
#include "AssetManagement/Scene/SceneAsset.h"
#include "AssetManagement/AssetManager.h"
#include <memory>

namespace Gromit
{
	struct ComponentInstance
	{
		int ComponentID;
		ComponentType ComponentType; //may not be required
		virtual void ApplyProperty(const std::string& name, const ComponentProperty& value) = 0;
	};
	struct TransformComponentInstance : public ComponentInstance
	{
		void ApplyProperty(const std::string& name, const ComponentProperty& value) override;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
	};
	struct MeshRendererComponentInstance : public ComponentInstance
	{
		void ApplyProperty(const std::string& name, const ComponentProperty& value) override;
		std::shared_ptr<MeshAsset> mesh;
		std::shared_ptr<MaterialAsset> material; //TODO HANDLE PROPERLY ONLY FOR TESTING

	};
	struct EntityInstance
	{
		int InstanceID;
		int GuiID;
		std::shared_ptr<EntityAsset> AssetRef; // TODO this might be weak ptr in future.

		std::unordered_map<ComponentType, ComponentInstance*> Components; //tmeporarily using type, limits to one component per entity.


		//	static EntityInstance* CreateInstance(int guid);
		//	static EntityInstance* CreateInstance(std::string name);
		//	static void DeleteInstance(EntityInstance* instance);

	private:
		//EntityAsset* m_asset; // shared pointer todo
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
		void  LoadScene(int guid); //Loads a scene at root(implied) and all entities required
		void  UnLoadScene(int guid); 
		EntityInstance* LoadEntity(const EntityReference& entityRef);

		static SceneInstance* m_activeScene;
		//static std::vector<std::unique_ptr <EntityInstance>> m_activeEntites;

	};
}