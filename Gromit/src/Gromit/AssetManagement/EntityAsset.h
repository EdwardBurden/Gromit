#pragma once
#include "Asset.h"
#include "Math/Math.h"
#include "AssetManagement/MeshAsset.h"
#include "AssetManagement/MaterialAsset.h"

namespace Gromit
{

	struct EntityAsset : public Asset
	{
		int mesh;
		int material;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(EntityAsset, guid, type, name, path, mesh, material)

			void Load() override
		{
			//
		}

	private:
	};

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
		ComponentType ComponentType;

	};

	struct TransformAsset : public ComponentAsset
	{
		glm::vec3 position; //may need to convert manually
		glm::vec3 rotation; //may need to convert manually
	};

	struct MeshRendererAsset : public ComponentAsset
	{
		MeshAsset mesh;
		MaterialAsset material;
	};
}