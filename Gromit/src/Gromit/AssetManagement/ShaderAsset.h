#pragma once
#include "Asset.h"
#include "AssetManagement/ShaderMetaData.h"

#include <sstream>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
namespace Gromit
{
	struct ShaderAsset : public Asset
	{
		using MetaType = ShaderMetaData;
		static constexpr size_t MAX_SHADER_SIZE = 1024; //temporary

		char m_source[MAX_SHADER_SIZE];
		ShaderType m_shaderType ;
		

		ShaderAsset(ShaderMetaData* metaData)
		{
			std::ifstream vertexFile(metaData->m_assetPath);
			std::stringstream stringStream;
			stringStream << vertexFile.rdbuf();
			size_t len = stringStream.str().size();
			std::strcpy(m_source, stringStream.str().c_str());
			vertexFile.close();
			stringStream.clear();
			m_shaderType = metaData->m_shaderType;
		}
	};
}