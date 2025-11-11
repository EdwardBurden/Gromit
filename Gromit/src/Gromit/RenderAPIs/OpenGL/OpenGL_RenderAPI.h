#pragma once
#include "RenderAPIs/RenderAPI.h"
#include "../../Logging/Logging.h"
#include "OpenGL_Window.h"
#include "OpenGL_Shader.h"
#include "OpenGL_VertexBuffer.h"
#include "OpenGL_IndexBuffer.h"
#include "OpenGL_BufferLayout.h"
#include "OpenGL_VertexArray.h"
#include "OpenGL_Context.h"
#include "OpenGL_Texture.h"
#include "OpenGL_Material.h"


namespace Gromit::OpenGL
{
	class OpenGL_RenderAPI : public RenderAPI
	{
	public:
		void InitWindows() override;
		void TerminateWindows() override;

		Window* CreateWindow(int x, int y, int width, int height, const char* title) override;
		Material* CreateMaterial(const std::shared_ptr<MaterialAsset>& material) override;
		Shader* CreateShader(const std::shared_ptr<ShaderAsset>& shader) override;
		VertexBuffer* CreateVertexBuffer(const Vertex* vertices, unsigned int size) override;
		IndexBuffer* CreateIndexBuffer(const unsigned int* indices, unsigned int size) override;
		VertexArray* CreateVertexArray() override;
		BufferLayout* CreateBufferLayout(const std::vector<BufferLayoutElement>& init) override;
		Context* CreateContext() override;
		Texture* CreateTexture(std::shared_ptr<TextureAsset> textureAsset) override;
		void DrawIndexes(int count) override;
	private:

	};
}