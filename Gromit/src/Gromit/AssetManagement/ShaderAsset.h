#pragma once
#include "Asset.h"
#include "AssetManagement/ShaderMetaData.h"

#include <sstream>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
namespace Gromit
{
	struct ShaderAsset : public AssetNew
	{
		using MetaType = ShaderMetaData;
		static constexpr size_t MAX_SHADER_SIZE = 1024; //temporary
		static constexpr size_t PoolCapacity = 50; //declared once

		char m_source[MAX_SHADER_SIZE];

		ShaderAsset(ShaderMetaData* metaData)
		{
			std::ifstream vertexFile(metaData->m_assetPath);
			std::stringstream stringStream;
			stringStream << vertexFile.rdbuf();
			size_t len = stringStream.str().size();
			std::strcpy(m_source, stringStream.str().c_str());
			vertexFile.close();
			stringStream.clear();
		}
	};
}