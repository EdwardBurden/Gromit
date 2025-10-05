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
		static RenderObject* CreateRenderObject(Context* context, MaterialAsset* material, MeshAsset* mesh, BufferLayout* layout);
		static void DrawRenderObject(RenderObject* obj, Camera* camera);
	};
}