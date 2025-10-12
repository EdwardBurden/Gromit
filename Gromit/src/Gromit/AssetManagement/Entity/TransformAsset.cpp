#include "AssetManagement/Entity/TransformAsset.h"

namespace Gromit
{
	TransformAsset::TransformAsset(int id, ComponentType type, nlohmann::json data) : ComponentAsset(id, type)
	{
		auto position = data["position"];
		position.at("x").get_to(m_position.x);
		position.at("y").get_to(m_position.y);
		position.at("z").get_to(m_position.z);

		auto rotation = data["rotation"];
		rotation.at("x").get_to(m_rotation.x);
		rotation.at("y").get_to(m_rotation.y);
		rotation.at("z").get_to(m_rotation.z);
	}
}