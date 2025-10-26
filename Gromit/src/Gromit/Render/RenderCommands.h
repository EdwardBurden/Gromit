#pragma once

#include "AssetManagement/Mesh/MeshAsset.h"
#include "AssetManagement/Material/MaterialAsset.h"
#include "RenderAPIs/RenderAPIs.h"
#include "Render/Render.h"
#include "ServiceLocator.h"
#include "Render/RenderObject.h"
#include "FrameTime.h"

namespace Gromit
{
	class RenderCommands
	{
	public:
		static RenderObject* CreateRenderObject(std::shared_ptr< MaterialAsset> material, std::shared_ptr< MeshAsset> mesh, BufferLayout* layout);
		static void DrawRenderObject(RenderObject* obj, Camera* camera);
	};
}