#pragma once
#include "../AssetManagement/Mesh/MeshAsset.h"

namespace Gromit
{
	class BufferLayout //todo needs moving into opengl namespace with virtual base
	{
	public:

		~BufferLayout() {}

		virtual void SetStride() = 0;
		virtual void SetAttributes() = 0;

	protected:
	};

}