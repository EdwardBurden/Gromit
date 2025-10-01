#pragma once
#include "Asset.h"
#include "AssetManagement/EntityMetaData.h"

namespace Gromit
{
	struct EntityAsset : public Asset
	{
		using MetaType = EntityMetaData;
		EntityAsset(EntityMetaData* metaData) : Asset(metaData->m_guid)
		{

		}
	};
}