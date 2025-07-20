#pragma once
#include "Asset.h"
namespace Gromit
{

	struct MeshAsset : public Asset
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MeshAsset, guid, type, name, path)

		void Load() override
		{
			//
		}
	};
}