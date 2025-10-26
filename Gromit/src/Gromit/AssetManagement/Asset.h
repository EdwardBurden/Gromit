#pragma once;
#include "AssetManagement/MetaData.h"
#include <memory>

namespace Gromit
{
	struct Asset 
	{
		Asset(std::shared_ptr<MetaData> metaData) : m_metaData(metaData)
		{
		
		}

		template<typename TMeta>
		std::shared_ptr<TMeta> GetMeta() const
		{
			return std::dynamic_pointer_cast<TMeta>(m_metaData);
		}

		int GetGuid() const { return m_metaData->GetGUID(); }
	protected:
		std::shared_ptr<MetaData> m_metaData;
	};
}