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
#include "../AssetManagement/ShaderAsset.h"
#include "../AssetManagement/TextureAsset.h" //todo
#include "../AssetManagement/MaterialAsset.h" //todo

namespace Gromit
{
	class RenderAPI
	{
	public:
		virtual void InitWindows() = 0;
		virtual void TerminateWindows() = 0;

		virtual Window* CreateWindow(int x, int y, int width, int height, const char* title) = 0;
		virtual Material* CreateMaterial(MaterialAsset* material) = 0;
		virtual Shader* CreateShader(ShaderAsset* shader) = 0;
		virtual VertexBuffer* CreateVertexBuffer(const Vertex* vertices, unsigned int size) = 0;;
		virtual IndexBuffer* CreateIndexBuffer(const unsigned int* indices, unsigned int size) = 0;
		virtual VertexArray* CreateVertexArray() = 0;
		virtual BufferLayout* CreateBufferLayout(std::initializer_list<Gromit::BufferLayoutElement> init) = 0;
		virtual Context* CreateContext() = 0;
		virtual Texture* CreateTexture(const TextureAsset& texture) = 0;
		virtual void DrawIndexes(int count) =0;
	};
}