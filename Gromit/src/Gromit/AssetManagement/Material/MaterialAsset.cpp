#include "AssetManagement/Material/MaterialAsset.h"
#include "AssetManagement/AssetDatabase.h"

namespace Gromit
{
	MaterialMetaData::MaterialMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, assetPath, data)
	{
		auto shaders = data["shaders"];
		for (size_t i = 0; i < shaders.size(); i++)
		{
			auto shader = shaders[i];
			int id;
			shader.at("guid").get_to(id);
			m_shaderIds.push_back(id);
			AddDependency(AssetType::Shader, id);
		}

		auto textures = data["textures"];
		for (size_t i = 0; i < textures.size(); i++)
		{
			auto texture = textures[i];
			int id;
			texture.at("guid").get_to(id);
			m_textureIds.push_back(id);
			AddDependency(AssetType::Texture, id);
		}
	}
}