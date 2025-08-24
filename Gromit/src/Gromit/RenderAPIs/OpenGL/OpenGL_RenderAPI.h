#pragma once
#include "../RenderAPI.h"
#include "../../Logging/Logging.h"
#include "OpenGL_Window.h"
#include "OpenGL_Shader.h"
#include "OpenGL_VertexBuffer.h"
#include "OpenGL_IndexBuffer.h"
#include "OpenGL_BufferLayout.h"
#include "OpenGL_VertexArray.h"


namespace Gromit::OpenGL
{
	class OpenGL_RenderAPI : public RenderAPI
	{
	public:
		void Temp() override;
		void SetGlobalContext() override;
		void InitWindows() override;
		void TerminateWindows() override;
		Window* CreateWindow(int x, int y, int width, int height, const char* title) override;
		Shader* CreateShader(const ShaderAsset& vert, const ShaderAsset& frag) override;
		VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size) override;
		IndexBuffer* CreateIndexBuffer(uint32_t* indices, uint32_t size) override;
		VertexArray* CreateVertexArray() override;
		void Update() override;
	private:
		Shader* m_tempShader;
		VertexArray* m_va;
	};
}