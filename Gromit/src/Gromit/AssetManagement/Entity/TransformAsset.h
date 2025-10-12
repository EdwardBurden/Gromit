#pragma once
#include "AssetManagement/Entity/EntityAsset.h"
#include "Math/Math.h"
namespace Gromit
{
	struct TransformAsset : public ComponentAsset
	{
	public:
		TransformAsset(int id, ComponentType type, nlohmann::json data);
		glm::vec3 m_position; //may need to convert manually
		glm::vec3 m_rotation; //may need to convert manually
	};
}