#pragma once
#include "AssetManagement/MetaData.h"
namespace Gromit
{
	struct MaterialMetaData : public MetaData
	{
	public:
		std::string m_assetPath;
		std::vector<int> m_shaderIds;
		std::vector<int> m_textureIds;

		MaterialMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, data)
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

			m_assetPath = assetPath + m_path;
		}
	};

}
