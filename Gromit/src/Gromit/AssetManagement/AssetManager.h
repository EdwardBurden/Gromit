#pragma once
#include "Asset.h"
#include "TextureAsset.h"
#include "../Logging/Logging.h"


namespace Gromit
{
	class  AssetManager
	{
	public:
		AssetManager() {
		}
		~AssetManager() {}

		void IdentifyAssets(std::string directory);


	private:
		std::map<int, Asset*> m_assetLookup;
	};
}