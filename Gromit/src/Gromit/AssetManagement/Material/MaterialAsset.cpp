#include "AssetManagement/Material/MaterialAsset.h"
#include "AssetManagement/AssetDatabase.h"
#include "AssetManagement/AssetManager.h"
#include "ServiceLocator.h"

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
			texture.at("guid").get_to(id); //to later add texture name
			m_textureIds.push_back(id);
			AddDependency(AssetType::Texture, id);
		}
	}

	MaterialAsset::MaterialAsset(std::shared_ptr<MaterialMetaData> metaData) : Asset(metaData)
	{
		for (auto& id : metaData->m_shaderIds)
		{
			std::shared_ptr<ShaderAsset> shader = ServiceLocator::GetService<AssetManager>()->LoadAsset<ShaderAsset>(id);
			m_shaders.push_back(shader);
		}

		for (auto& id : metaData->m_textureIds)
		{
			std::shared_ptr<TextureAsset> shader = ServiceLocator::GetService<AssetManager>()->LoadAsset<TextureAsset>(id);
			m_textures.push_back(shader);
		}
	}
	MaterialAsset::~MaterialAsset() 
	{
		m_shaders.clear();
		m_textures.clear();
	}


	REGISTER_ASSET_HANDLER(MaterialAssetHandler, AssetType::Material, MaterialAsset, MaterialMetaData, 8);
}