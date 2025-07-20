#pragma once
#include "Asset.h"
namespace Gromit
{

	struct ModelAsset : public Asset
	{
		int mesh;
		int material;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ModelAsset, guid, type, name, path, mesh, material)

		void Load() override
		{
			//
		}

	private:
		MeshAsset m_mesh;
		MaterialAsset m_material;
	};
}