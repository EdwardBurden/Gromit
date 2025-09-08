#pragma once
#include "Asset.h"
#include "Math/Math.h"
#include "AssetManagement/MeshAsset.h"
#include "AssetManagement/MaterialAsset.h"

namespace Gromit
{
	enum class ComponentType
	{
		Transform = 0,
		MeshRenderer = 1
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(ComponentType,
		{
			{ComponentType::Transform, "Transform"},
			{ComponentType::MeshRenderer , "MeshRenderer"}
		});


	struct ComponentAsset
	{
		ComponentType componentType;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentAsset, componentType);

	};

	struct TransformAsset : public ComponentAsset
	{
		glm::vec3 position; //may need to convert manually
		glm::vec3 rotation; //may need to convert manually

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformAsset, componentType, position, rotation);
	};

	struct MeshRendererAsset : public ComponentAsset
	{
		int mesh; //todo will have all loaded assets ref counted in assetmanager and ref here instead
		int material;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MeshRendererAsset, componentType, mesh, material);
	};


	struct EntityAsset : public Asset
	{
	public:
		std::vector<ComponentAsset*> components;

		//NLOHMANN_DEFINE_TYPE_INTRUSIVE(EntityAsset, guid, type, name, path, components);

		void Load() override
		{
			//
		}

	private:
	};


	void from_json(const nlohmann::json& j, EntityAsset& entity) {
		j.at("guid").get_to(entity.guid);
		j.at("type").get_to(entity.type);
		j.at("name").get_to(entity.name);
		j.at("path").get_to(entity.path);
		entity.components.clear();

		auto c = j["components"];
		for (size_t i = 0; i < c.size(); i++)
		{
			auto obj = c[i];

			ComponentAsset* cAs = new ComponentAsset(); //needs to be based on type
			entity.components.push_back(cAs);

			obj.at("componentType").get_to(entity.components[i]->componentType);
			auto comp = obj["componentType"];
		}


	}



}