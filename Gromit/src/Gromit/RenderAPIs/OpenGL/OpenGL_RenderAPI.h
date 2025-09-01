#pragma once
#include "../RenderAPI.h"
#include "../../Logging/Logging.h"
#include "OpenGL_Window.h"
#include "OpenGL_Shader.h"
#include "OpenGL_VertexBuffer.h"
#include "OpenGL_IndexBuffer.h"
#include "OpenGL_BufferLayout.h"
#include "OpenGL_VertexArray.h"
#include "OpenGL_Context.h"
#include "OpenGL_Texture.h"


namespace Gromit::OpenGL
{
	class OpenGL_RenderAPI : public RenderAPI
	{
	public:
		void InitWindows() override;
		void TerminateWindows() override;

		Window* CreateWindow(int x, int y, int width, int height, const char* title) override;
		Shader* CreateShader(const ShaderAsset& vert, const ShaderAsset& frag) override;
		VertexBuffer* CreateVertexBuffer(const std::vector<Vertex>& vertices) override;
		IndexBuffer* CreateIndexBuffer(const std::vector<unsigned int>& indices) override;
		VertexArray* CreateVertexArray() override;
		BufferLayout* CreateBufferLayout(std::initializer_list<Gromit::BufferLayoutElement> init) override;
		Context* CreateContext() override;
		Texture* CreateTexture(const TextureAsset& texture) override;
		void DrawIndexes(int count) override;
	private:

	};
}