#pragma once
#include "AssetManagement/Entity/EntityAsset.h"
#include "AssetManagement/Mesh/MeshAsset.h"
#include "AssetManagement/Material/MaterialAsset.h"
#include "ServiceLocator.h"
#include "AssetManagement/AssetManager.h"
#include "AssetManagement/Scene/SceneAsset.h"

namespace Gromit
{
	struct ComponentInstance
	{
		int ComponentID;
		ComponentType ComponentType; //may not be required
		virtual void ApplyProperty(const std::string& name, const ComponentProperty& value) = 0;
		virtual void SetComponent(const std::unique_ptr<ComponentAsset>& compAsset) = 0;
		virtual void OnDestory() = 0;



		template<typename TComponent>
		static std::unique_ptr<TComponent> CreateComponentInstance(int key, const std::unique_ptr<ComponentAsset>& component, const EntityReference& entityRef)
		{
			std::unique_ptr<TComponent> instance = std::make_unique<TComponent>();
			instance->SetComponent(component);

			const auto& overrides = entityRef.GetOverrides();
			auto iterator = overrides.find(key);
			if (iterator != entityRef.Overrides.end())
			{
				for (const auto& [propertyName, propertyValue] : iterator->second->Properties)
				{
					instance->ApplyProperty(propertyName, propertyValue);
				}
			}
			return instance;
		}
	};

	struct TransformComponentInstance : public ComponentInstance
	{
		void ApplyProperty(const std::string& name, const ComponentProperty& value) override;
		void SetComponent(const std::unique_ptr<ComponentAsset>& compAsset) override;
		void OnDestory() override;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
	};
	struct MeshRendererComponentInstance : public ComponentInstance
	{
		void ApplyProperty(const std::string& name, const ComponentProperty& value) override;
		void SetComponent(const std::unique_ptr<ComponentAsset>& compAsset) override;
		void OnDestory() override;
		std::shared_ptr<MeshAsset> mesh;
		std::shared_ptr<MaterialAsset> material; //TODO HANDLE PROPERLY ONLY FOR TESTING
	};
}