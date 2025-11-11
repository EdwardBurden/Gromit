#pragma once
#include "RenderAPIs/BufferLayout.h"
#include "RenderAPIs/Context.h"
#include "RenderAPIs/IndexBuffer.h"
#include "RenderAPIs/RenderAPI.h"
#include "RenderAPIs/Shader.h"
#include "RenderAPIs/Texture.h"
#include "RenderAPIs/VertexArray.h"
#include "RenderAPIs/VertexBuffer.h"
#include "RenderAPIs/Window.h"
#include "RenderAPIs/Material.h"
#include "Math/Math.h"
#include "AssetManagement/Shader/ShaderAsset.h"
#include "AssetManagement/Texture/TextureAsset.h" //todo
#include "AssetManagement/Material/MaterialAsset.h" //todo

namespace Gromit
{
	class RenderAPI
	{
	public:
		virtual void InitWindows() = 0;
		virtual void TerminateWindows() = 0;

		virtual Window* CreateWindow(int x, int y, int width, int height, const char* title) = 0;
		virtual Material* CreateMaterial(const std::shared_ptr<MaterialAsset>& material) = 0;
		virtual Shader* CreateShader(const std::shared_ptr<ShaderAsset>& shader) = 0;
		virtual VertexBuffer* CreateVertexBuffer(const Vertex* vertices, unsigned int size) = 0;;
		virtual IndexBuffer* CreateIndexBuffer(const unsigned int* indices, unsigned int size) = 0;
		virtual VertexArray* CreateVertexArray() = 0;
		virtual BufferLayout* CreateBufferLayout(const std::vector<BufferLayoutElement>& init) = 0;
		virtual Context* CreateContext() = 0;
		virtual Texture* CreateTexture(std::shared_ptr<TextureAsset> textureAsset) = 0;
		virtual void DrawIndexes(int count) =0;
	};
}