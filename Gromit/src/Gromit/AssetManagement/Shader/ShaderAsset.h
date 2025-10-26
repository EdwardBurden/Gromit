#pragma once
#include "AssetManagement/Asset.h"

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
		ShaderMetaData(int guid, std::string assetPath, nlohmann::json data);
		ShaderType m_shaderType;
	};

	struct ShaderAsset : public Asset
	{
		ShaderAsset(std::shared_ptr<ShaderMetaData> metaData);
		const ShaderType GetShaderType() const { return GetMeta<ShaderMetaData>()->m_shaderType; }
		const char* GetSource() const { return m_source; }
	private:
		static constexpr size_t MAX_SHADER_SIZE = 1024; //temporary
		char m_source[MAX_SHADER_SIZE];
	};
}