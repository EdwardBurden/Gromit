#pragma once
#include "../Core.h"
#include "Window.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"
#include "Texture.h"

#include "Context.h"
#include "../AssetManagement/ShaderAsset.h"
#include "../AssetManagement/TextureAsset.h"

namespace Gromit
{
	class RenderAPI
	{
	public:
		virtual void InitWindows() = 0;
		virtual void TerminateWindows() = 0;

		virtual Window* CreateWindow(int x, int y, int width, int height, const char* title) = 0;
		virtual Shader* CreateShader(const ShaderAsset& vert, const ShaderAsset& frag) = 0;
		virtual VertexBuffer* CreateVertexBuffer(const std::vector<Vertex>& vertices) = 0;;
		virtual IndexBuffer* CreateIndexBuffer(const std::vector<unsigned int>& indices) = 0;
		virtual VertexArray* CreateVertexArray() = 0;
		virtual BufferLayout* CreateBufferLayout(std::initializer_list<Gromit::BufferLayoutElement> init) = 0;
		virtual Context* CreateContext() = 0;
		virtual Texture* CreateTexture(const TextureAsset& texture) = 0;
		virtual void DrawIndexes(int count) =0;
	};
}