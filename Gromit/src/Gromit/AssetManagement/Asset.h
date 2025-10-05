#pragma once;
#include "AssetManagement/MetaData.h"

namespace Gromit
{
	struct Asset 
	{
		Asset(MetaData* metaData) : m_metaData(metaData)
		{
		
		}

		template<typename TMeta>
		TMeta* GetMeta() const
		{
			return static_cast<TMeta*>(m_metaData);
		}

		int GetGuid() const { return m_metaData->GetGUID(); }
	protected:
		MetaData* m_metaData; //todo improve pointers
	};
}