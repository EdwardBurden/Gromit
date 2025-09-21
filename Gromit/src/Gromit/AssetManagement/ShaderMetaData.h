#pragma once
#include "AssetManagement/MetaData.h"

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


	struct ShaderMetaData : public MetaData
	{
	public:
		std::string m_assetPath;
		ShaderType m_shaderType;

		ShaderMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, data)
		{
			data.at("shaderType").get_to(m_shaderType);
			m_assetPath = assetPath + m_path;
		}
	};

}