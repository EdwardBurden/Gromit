#pragma once
#include "AssetManagement/Asset.h"
#include "AssetManagement/MetaData.h"

namespace Gromit
{
	struct AssetRecord
	{
		MetaData* metaData;
		Asset* asset = nullptr;
		int refCount = 0;
		bool permanent = false;

		AssetRecord(MetaData* meta)
		{
			metaData = meta;
		}
	};
}