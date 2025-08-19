#pragma once
#include "Asset.h"
#include "TextureAsset.h"
#include "ShaderAsset.h"
#include "MaterialAsset.h"
#include "MeshAsset.h"
#include "ModelAsset.h"
#include "../Logging/Logging.h"
#include "../IEngineService.h"


namespace Gromit
{
	class GROMIT_API AssetManager : public IEngineService
	{
	public:
		AssetManager()
		{
			std::cout << "AssetManager Constructor" << std::endl;
		}

		void IdentifyAssets(std::string directory);
		void LoadAsset(int guid);
		void OnStartUp() override;
		void OnShutDown() override;
		bool OnUpdate();
	private:

		template<typename T>
		void IdentifyAsset(Asset& assetbase, json data)
		{
			auto* m = new T();
			from_json(data, *m);
			m_assetLookup[assetbase.guid] = m;
			//test = assetbase.guid;
			GL_INFO(m->name);
		}

		template<typename T>
		void TryLoadAsset(Asset* assetbase)
		{
			T* derivedPtr = static_cast<T*>(assetbase);
			if (!derivedPtr->isloaded)
			{
				derivedPtr->Load();
			}
			derivedPtr->RefCount++;
		}
		std::map<int, Asset*> m_assetLookup;
	};
}