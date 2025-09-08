#pragma once
#include "AssetManagement/Asset.h"
#include "Logging/Logging.h"
#include "IEngineService.h"
#include <json.hpp>

namespace Gromit
{
	class GROMIT_API AssetManager : public IEngineService
	{
	public:
		AssetManager()
		{
			std::cout << "AssetManager Constructor" << std::endl;
		}
		void LoadIdentifiedAsset();
		void IdentifyAssets(std::string directory);
		void LoadAsset(int guid);
		void OnStartUp() override;
		void OnShutDown() override;
		bool OnUpdate();
		std::string pathTemp;

		template<typename T>
		T* GetAsset(int guid)
		{
			auto asset = m_assetLookup[guid];
			T* derivedPtr = static_cast<T*>(asset);
			return derivedPtr;
		}


	private:

		template<typename T>
		void IdentifyAsset(int guid, std::string fullPath, nlohmann::json data)
		{
			auto* m = new T();
			from_json(data, *m);
			m->fullPath = fullPath;
			m->assetPath = pathTemp + m->path;
			m_assetLookup[guid] = m;
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
				derivedPtr->isloaded = true;
			}
			derivedPtr->RefCount++;
		}

		std::map<int, Asset*> m_assetLookup;
	};
}