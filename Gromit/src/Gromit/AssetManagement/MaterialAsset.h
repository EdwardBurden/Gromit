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

		MaterialAsset(MaterialMetaData* metaData)
		{
			m_shaders = metaData->m_shaderIds; //then load if not already
			for (size_t i = 0; i < m_shaders.size(); i++)
			{
				//ServiceLocator::GetService<AssetManager>()->LoadAsset<ShaderAsset>(m_shaders[i]); //load so its already available
			}
			m_textures = metaData->m_textureIds; //then load
		}

		std::vector<int> GetShaderIds() 
		{
			return m_shaders;
		}


		//todo access methods to metadata
	};
}