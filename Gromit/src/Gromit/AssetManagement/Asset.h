#pragma once;

#include <json.hpp>
using json = nlohmann::json;

namespace Gromit
{
	enum class AssetType
	{
		Texture = 0
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(AssetType, { {AssetType::Texture, "texture"} });

	struct Asset
	{
		int guid;
		AssetType type;
		std::string name;
		std::string path;
	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Asset, guid, type, name, path)
		std::string fullPath;
		bool isloaded;
		int RefCount;

	};
}