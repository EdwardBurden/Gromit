#pragma once;

#include <json.hpp>

namespace Gromit
{
	struct AssetNew {};

	enum class AssetType
	{
		Texture = 0,
		Shader = 1,
		Material = 2,
		Mesh = 3,
		Entity = 4
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(AssetType,
		{
			{ AssetType::Texture, "Texture"},
			{ AssetType::Shader, "Shader" },
			{ AssetType::Material, "Material" },
			{ AssetType::Mesh, "Mesh" },
			{ AssetType::Entity, "Entity" }
		});

	struct Asset
	{
		int guid;
		AssetType type;
		std::string name;
		std::string path;
	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Asset, guid, type, name, path)
		
			
		std::string fullPath;
		std::string assetPath;
		bool isloaded;
		int RefCount;


		virtual void Load() {}

	};
}