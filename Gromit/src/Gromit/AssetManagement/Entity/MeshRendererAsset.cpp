#include "AssetManagement/Entity/MeshRendererAsset.h"

namespace Gromit
{
	MeshRendererAsset::MeshRendererAsset(int id, ComponentType type, nlohmann::json data) : ComponentAsset(id, type)
	{
		data.at("mesh").get_to(m_mesh);
		data.at("material").get_to(m_material);
	}

	const std::vector<AssetDependency> MeshRendererAsset::GetDependencies() const
	{
		return
		{
			{ AssetType::Mesh, m_mesh },
			{ AssetType::Material, m_material }
		};
	}
}