#include "Render/RenderCommands.h"

namespace Gromit
{
	RenderObject* RenderCommands::test = nullptr;

	RenderObject* RenderCommands::CreateRenderObject(Context* context)
	{
		///////////////TEMP PART

		BufferLayout* layout = Renderer::GetAPI()->CreateBufferLayout(
			{
				{ShaderDataType::Float3 , "position"},
				{ShaderDataType::Float3 , "normal"},
				{ShaderDataType::Float2 , "texCoords"}
			});
		const auto& manager = ServiceLocator::GetService<AssetManager>();
		MeshAsset* mesh = manager->GetAsset<MeshAsset>(32422333);
		ShaderAsset* vert = manager->GetAsset<ShaderAsset>(545);
		ShaderAsset* frag = manager->GetAsset<ShaderAsset>(123434);
		TextureAsset* smileTextureAsset = manager->GetAsset<TextureAsset>(345455675675);
		//////////////

		std::vector<VertexArray*> vArrays;
		auto smileTexture = Renderer::GetAPI()->CreateTexture(*smileTextureAsset);
		auto shader = Renderer::GetAPI()->CreateShader(*vert, *frag);
		auto m_tempVB = Renderer::GetAPI()->CreateVertexBuffer(mesh->vertices);
		m_tempVB->SetLayout(layout);
		auto m_tempIB = Renderer::GetAPI()->CreateIndexBuffer(mesh->indices);
		for (Window* window : context->GetWindows())
		{
			window->Activate();
			auto va = Renderer::GetAPI()->CreateVertexArray();
			va->Bind();
			va->SetIndexBuffer(m_tempIB);
			va->SetVertexBuffer(m_tempVB);
			shader->Bind();
			smileTexture->Bind();
			va->Unbind();
			vArrays.push_back(va);
		}
		test = new RenderObject(shader, smileTexture, vArrays, m_tempVB, m_tempIB, context);
		return test;
	}
}