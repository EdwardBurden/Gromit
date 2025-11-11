#pragma once
#include "Render/RenderObject.h"
#include "EntityManagement/ComponentInstance.h"
#include "Camera.h"
#include "Renderer.h"

namespace Gromit
{
	class RenderCommands
	{
	public:

		static std::unique_ptr<RenderObject> CreateRenderObject(const MeshRendererComponentInstance& meshInstance);
		static void DrawRenderObject(const RenderObject& renderObject, const TransformComponentInstance& transform, Camera* camera);
	};
}