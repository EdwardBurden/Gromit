#include "AssetManager.h"
#include "AssetManagement/AssetManagement.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace fs = std::filesystem;
using json = nlohmann::json;
namespace Gromit
{
	void AssetManager::OnStartUp()
	{
		//IdentifyAssets("assets"); //temp
	}

	void AssetManager::OnShutDown()
	{
		//todo release all
	}

	bool AssetManager::OnUpdate()
	{
		//todo handle load queu for assets
		return false;
	}

	void AssetManager::IdentifyAssets(std::string directory) // only loads json
	{
		fs::path current = fs::current_path();
		GL_INFO(directory);
		current /= directory;
		pathTemp = current.string();
		//	std::stringstream buffer;
			//int test = 0;
		for (const auto& entry : fs::directory_iterator(current))
		{
			fs::path p = entry.path();
			if (p.extension() == ".json") {
				std::ifstream f(p);
				std::stringstream buffer;
				buffer << f.rdbuf(); // read entire file into buffer
				GL_INFO(buffer.str());
				if (f.good() && f.is_open() && !buffer.str().empty())
				{
					json data = json::parse(buffer);
					AssetType type = data["type"].template get<AssetType>();
					auto guid = data["guid"].template get<int>();
					switch (type)
					{
					case AssetType::Texture:
						db.GetOrLoadMetadata<TextureAsset>(guid, pathTemp, data);
						//IdentifyAsset<TextureAsset>(assetbase.guid, p.string(), data);
						break;
					case AssetType::Shader:
						db.GetOrLoadMetadata<ShaderAsset>(guid, pathTemp, data);
						//IdentifyAsset<ShaderAsset>(assetbase.guid, p.string(), data);
						break;
					case AssetType::Material:
						//IdentifyAsset<MaterialAsset>(assetbase.guid, p.string(), data);
						break;
					case AssetType::Mesh:
						db.GetOrLoadMetadata<MeshAsset>(guid, pathTemp, data);
					//	IdentifyAsset<MeshAsset>(assetbase.guid, p.string(), data);
						break;
					case AssetType::Entity:
						//IdentifyAsset<EntityAsset>(assetbase.guid, p.string(), data);
						break;
					default:
						break;
					}
				}
			}
		}
		//auto asset = m_assetLookup[test];
		//TextureAsset* derivedPtr = static_cast<TextureAsset*>(asset);

	}

	//todo will be need ot be template
	/*void AssetManager::LoadAsset(int guid)
	{
		db.GetOrLoadAsset<MeshAsset>(guid);
		auto asset = m_assetLookup[guid];
		switch (asset->type)
		{
		case AssetType::Texture:
			TryLoadAsset<TextureAsset>(asset);
			break;
		case AssetType::Shader:
			TryLoadAsset<ShaderAsset>(asset);
			break;
		case AssetType::Material:
			TryLoadAsset<MaterialAsset>(asset);
			break;
		case AssetType::Mesh:
			
		//	TryLoadAsset<MeshAsset>(asset);
			break;
		case AssetType::Entity:
			TryLoadAsset<EntityAsset>(asset);
			break;
		default:
			break;
		}
	}*/
}