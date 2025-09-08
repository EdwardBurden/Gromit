#pragma once
#include "EntityManagement/Component.h"
#include "AssetManagement/EntityAsset.h"


namespace Gromit
{
	struct Entity
	{
	public:
		Entity(const EntityAsset& entityAsset) 
		{
			//entityAsset.
			m_components.clear();
		}


	private:
		std::vector<std::unique_ptr<Component>> m_components;
	};

}
