#pragma once
#include "Asset.h"
//#include "AssetManagement/AssetManager.h"
#include "AssetManagement/MaterialMetaData.h"
#include "ServiceLocator.h"

namespace Gromit
{

	struct MaterialAsset : public Asset
	{
		using MetaType = MaterialMetaData;

	private:
		std::vector<int> m_shaders;
		std::vector<int> m_textures;

	public:

		MaterialAsset(MaterialMetaData* metaData) : Asset(metaData->m_guid)
		{
			m_shaders = metaData->m_shaderIds;
			m_textures = metaData->m_textureIds;
		}

		std::vector<int> GetShaderIds() 
		{
			return m_shaders;
		}

		std::vector<int> GetTextureIds()
		{
			return m_textures;
		}


		//todo access methods to metadata
	};
}