#pragma once
#include <string>
#include <map>
#include "Asset.h"

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