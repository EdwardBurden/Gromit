#pragma once
#include "Asset.h"
namespace Gromit
{
	enum class ShaderType {
		Fragment = 0,
		Vertex = 1
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(ShaderType,
		{
				{ShaderType::Fragment, "Fragment"},
				{ShaderType::Vertex , "Vertex"}
		});

	struct ShaderAsset : public Asset
	{
		ShaderType shaderType;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ShaderAsset, guid, type, name, path, shaderType)


	};
}