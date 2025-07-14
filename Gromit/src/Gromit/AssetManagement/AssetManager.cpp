#include "AssetManager.h"
#include <json.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
		//int test = 0;
		for (const auto& entry : fs::directory_iterator(current)) 
		{
			fs::path p = entry.path();
			if (p.extension() == ".json") {
				std::ifstream f(p);
				buffer << f.rdbuf(); // read entire file into buffer
				GL_INFO(buffer.str());
				if (f.good() && f.is_open() && !buffer.str().empty()) 
				{
					json data = json::parse(buffer);
					Asset assetbase = data.template get<Asset>();
					assetbase.fullPath = p.string();

					switch (assetbase.type)
					{
					case AssetType::Texture:
					{
						auto* t = new TextureAsset();
						from_json(data, *t);
						m_assetLookup[assetbase.guid] = t;
						//test = assetbase.guid;
						GL_INFO(t->name);
						break;
					}
					case AssetType::Shader:
					{
						auto* s = new ShaderAsset();
						from_json(data, *s);
						m_assetLookup[assetbase.guid] = s;
						//test = assetbase.guid;
						GL_INFO(s->name);
						break;
					}
					case AssetType::Material:
					{
						auto* m = new MaterialAsset();
						from_json(data, *m);
						m_assetLookup[assetbase.guid] = m;
						//test = assetbase.guid;
						GL_INFO(m->name);
						break;
					}
					default:
						break;
					}
				}
				buffer.clear();
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
		{
			TextureAsset* derivedPtr = static_cast<TextureAsset*>(asset);
			if (derivedPtr->isloaded) {
				derivedPtr->RefCount++;
				return;// derivedPtr->data;
			}
			int width, height, nrChannels;
			derivedPtr->data = stbi_load(asset->path.c_str(), &width, &height, &nrChannels, 0);
			derivedPtr->RefCount++;
			break;
			//todo have some system to unload when refcount goes to 0
		}
		case AssetType::Shader:
		{
			ShaderAsset* derivedPtr = static_cast<ShaderAsset*>(asset);
			if (derivedPtr->isloaded) {
				derivedPtr->RefCount++;
				return;// derivedPtr->data;
			}
			//TODO load shader
			derivedPtr->RefCount++;
			break;
		}
		case AssetType::Material:
		{
			MaterialAsset* derivedPtr = static_cast<MaterialAsset*>(asset);
			if (derivedPtr->isloaded) {
				derivedPtr->RefCount++;
				return;// derivedPtr->data;
			}
			///TODO, check shaders aRE LOADED, IF not load each and all textures required
			derivedPtr->RefCount++;
			break;
		}

		default:
			break;
		}
	}
}