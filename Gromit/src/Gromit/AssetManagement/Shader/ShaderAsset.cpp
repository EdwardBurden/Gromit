#include "AssetManagement/Shader/ShaderAsset.h"
#include "AssetManagement/AssetDatabase.h"

namespace Gromit
{
	ShaderMetaData::ShaderMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, assetPath, data)
	{
		data.at("shaderType").get_to(m_shaderType);
	}

	ShaderAsset::ShaderAsset(ShaderMetaData* metaData) : Asset(metaData)
	{
		std::ifstream vertexFile(metaData->GetAssetPath());
		std::stringstream stringStream;
		stringStream << vertexFile.rdbuf();
		size_t len = stringStream.str().size();
		std::strcpy(m_source, stringStream.str().c_str());
		vertexFile.close();
		stringStream.clear();
	}

	REGISTER_ASSET_HANDLER(ShaderAssetHandler, AssetType::Shader, ShaderAsset, ShaderMetaData, 8);
}