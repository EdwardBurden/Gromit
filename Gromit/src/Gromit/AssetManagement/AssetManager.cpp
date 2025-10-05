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
				//GL_INFO(buffer.str());
				if (f.good() && f.is_open() && !buffer.str().empty())
				{
					json data = json::parse(buffer);
					AssetType type = data["type"].template get<AssetType>();
					auto guid = data["guid"].template get<int>();

					db.LoadMetadata(guid, type, pathTemp, data);
				}
			}
		}
		//auto asset = m_assetLookup[test];
		//TextureAsset* derivedPtr = static_cast<TextureAsset*>(asset);

	}

	//todo will be need ot be template
	Asset* AssetManager::LoadAsset(int guid)
	{
		AssetType type = db.FindAssetType(guid);
		std::vector<AssetDependency> dependencies = db.GetDependencies(guid);

		for (auto& depencency : dependencies)
		{
			LoadAsset(depencency.guid);
		}

	return 	db.LoadAsset(guid, type);
	}
}