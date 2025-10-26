#pragma once
#include "AssetManagement/Asset.h"
#include "AssetManagement/MetaData.h"
#include <iostream>
#include <memory>

namespace Gromit
{
	struct AssetRecord
	{
		std::shared_ptr<MetaData> m_metaData;
		std::shared_ptr<Asset> m_asset;
		bool m_permanent = false;

		AssetRecord() = default;
		AssetRecord(std::shared_ptr<MetaData> meta)	: m_metaData(std::move(meta)) 
		{
		}
	};
}