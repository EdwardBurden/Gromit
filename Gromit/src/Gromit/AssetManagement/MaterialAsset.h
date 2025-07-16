#pragma once
#include "Asset.h"
namespace Gromit
{

	struct MaterialAsset : public Asset
	{
		int vertex;
		int fragment;
		int mainTex;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MaterialAsset, guid, type, name, path, vertex, fragment, mainTex)

		void Load() override
		{
			//
		}
	};
}