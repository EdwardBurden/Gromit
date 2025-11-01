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
		void ClearIdentifiedAsset(std::string directory);
		//void LoadAsset(int guid);
		void OnStartUp() override;
		void OnShutDown() override;
		bool OnUpdate();



		template<typename T>
		std::shared_ptr<T> LoadAsset(int guid)
		{
			std::shared_ptr<Asset> ptr = LoadAsset(guid);
			return std::static_pointer_cast<T>(ptr);
		//	return 	static_cast<T*>(ptr);
		}

		void UnLoadAsset(int guid);
	private:
		std::shared_ptr<Asset> LoadAsset(int guid);
		//void UnLoadAsset(int guid);

		AssetDatabase db;
		std::string pathTemp;
	};
}