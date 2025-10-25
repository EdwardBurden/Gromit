#pragma once
#include "AssetManagement/Entity/EntityAsset.h"

namespace Gromit
{
	struct MeshRendererAsset : public ComponentAsset
	{
	public:
		MeshRendererAsset(int id, ComponentType type, nlohmann::json data);
		const std::vector<AssetDependency> GetDependencies() const override;
		int m_mesh;
		int m_material;
	};
}