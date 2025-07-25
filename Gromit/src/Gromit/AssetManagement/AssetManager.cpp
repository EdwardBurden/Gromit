#include "AssetManager.h"
#include <json.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace fs = std::filesystem;
using json = nlohmann::json;
namespace Gromit
{	
	void AssetManager::OnStartUp()
	{
		IdentifyAssets("assets"); //temp
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
					Asset assetbase = data.template get<Asset>(); //todo could just get the one variable out instead
					assetbase.fullPath = p.string();

					switch (assetbase.type)
					{
					case AssetType::Texture:
						IdentifyAsset<TextureAsset>(assetbase, data);
						break;
					case AssetType::Shader:
						IdentifyAsset<ShaderAsset>(assetbase, data);
						break;
					case AssetType::Material:
						IdentifyAsset<MaterialAsset>(assetbase, data);
						break;
					case AssetType::Mesh:
						IdentifyAsset<MeshAsset>(assetbase, data);
						break;
					case AssetType::Model:
						IdentifyAsset<ModelAsset>(assetbase, data);
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

	void AssetManager::LoadAsset(int guid)
	{
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
			TryLoadAsset<MeshAsset>(asset);
			break;
		case AssetType::Model:
			TryLoadAsset<ModelAsset>(asset);
			break;
		default:
			break;
		}
	}
}