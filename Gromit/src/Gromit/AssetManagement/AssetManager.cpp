#include "AssetManager.h"
#include "TextureAsset.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

void AssetManager::IdentifyAssets(std::string directory) // only loads json
{
	fs::path current = fs::current_path();
	std::cout << "You are in: " << current << "\n";
	current /= directory;
	std::stringstream buffer;

	int test = 0;
	for (const auto& entry : fs::directory_iterator(current)) {
		fs::path p = entry.path();
		if (p.extension() == ".json") {
			std::ifstream f(p);
			buffer << f.rdbuf(); // read entire file into buffer
			std::cout << buffer.str() << std::endl;
			if (f.good() && f.is_open() && !buffer.str().empty()) {
				json data = json::parse(buffer);
				Asset assetbase = data.template get<Asset>();
				switch (assetbase.type)
				{
				case AssetType::Texture:
				{
					auto* t = new TextureAsset();
					from_json(data, *t);
					m_assetLookup[assetbase.guid] = t;
					test = assetbase.guid;
				}
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


