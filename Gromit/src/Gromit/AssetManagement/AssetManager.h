#pragma once
#include "AssetManagement/Asset.h"
#include "Logging/Logging.h"
#include "IEngineService.h"
#include "AssetManagement/AssetDatabase.h"
#include <json.hpp>


namespace Gromit
{
	class GROMIT_API AssetManager : public IEngineService
	{
	public:
		AssetManager() : db()
		{
			std::cout << "AssetManager Constructor" << std::endl;
		}

		~AssetManager()
		{
			//db.Test();
		}

		void IdentifyAssets(std::string directory);
		void LoadAsset(int guid);
		void OnStartUp() override;
		void OnShutDown() override;
		bool OnUpdate();

		template<typename T>
		T* LoadAsset(int guid)
		{
			return db.GetOrLoadAsset<T>(guid);
		}


	private:
		AssetDatabase db;
		std::string pathTemp;
	};
}