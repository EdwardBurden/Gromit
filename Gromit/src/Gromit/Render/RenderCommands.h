#pragma once

#include "AssetManagement/ShaderAsset.h" //todo would just need asset
#include "AssetManagement/MeshAsset.h"
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
		static RenderObject* CreateRenderObject(Context* context, TextureAsset* texture, ShaderAsset* vert, ShaderAsset* frag, MeshAsset* mesh, BufferLayout* layout);
		static void DrawRenderObject(RenderObject* obj, Camera* camera);
	};
}