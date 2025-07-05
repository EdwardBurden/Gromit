#include "AssetManager.h"
#include <json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;
namespace Gromit
{
	void AssetManager::IdentifyAssets(std::string directory) // only loads json
	{
		fs::path current = fs::current_path();
		GL_INFO(directory);
		current /= directory;
		std::stringstream buffer;
		int test = 0;
		for (const auto& entry : fs::directory_iterator(current)) {
			fs::path p = entry.path();
			if (p.extension() == ".json") {
				std::ifstream f(p);
				buffer << f.rdbuf(); // read entire file into buffer
				GL_INFO(buffer.str());
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
						GL_INFO(t->name);
					}
					break;
					default:
						break;
					}
				}
			}
		}
		auto asset = m_assetLookup[test];
		TextureAsset* derivedPtr = static_cast<TextureAsset*>(asset);

	}


}