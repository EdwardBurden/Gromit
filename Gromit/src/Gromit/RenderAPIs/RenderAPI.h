#pragma once
#include "../Core.h"
#include "Window.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
//#include "BufferLayout.h"
#include "VertexArray.h"
#include "../AssetManagement/ShaderAsset.h"

namespace Gromit 
{
	class RenderAPI
	{
	public:
		virtual void Temp() = 0;
		virtual void SetGlobalContext() = 0;
		virtual void InitWindows() = 0;
		virtual void TerminateWindows() = 0;
		virtual Window* CreateWindow(int x, int y, int width, int height, const char* title) = 0;
		virtual Shader* CreateShader(const ShaderAsset& vert, const ShaderAsset& frag) = 0;
		virtual VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size) = 0;
		virtual IndexBuffer* CreateIndexBuffer(uint32_t* indices, uint32_t size) = 0;
		virtual VertexArray* CreateVertexArray() = 0;
		virtual void Update() = 0;
	};
}