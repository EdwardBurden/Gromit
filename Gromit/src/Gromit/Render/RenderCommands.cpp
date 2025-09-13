#include "Render/RenderCommands.h"

namespace Gromit
{
	RenderObject* RenderCommands::CreateRenderObject(Context* context, TextureAsset* texture, ShaderAsset* vert, ShaderAsset* frag, MeshAsset* mesh, BufferLayout* layout)
	{
		std::vector<VertexArray*> vArrays;
		auto smileTexture = Renderer::GetAPI()->CreateTexture(*texture);
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
		return new RenderObject(shader, smileTexture, vArrays, m_tempVB, m_tempIB, context);
	}

	void RenderCommands::DrawRenderObject(RenderObject* obj, Camera* camera) //todo pass in time plus other render params
	{
		int index = 0;
		for (auto window : obj->m_context->GetWindows())
		{
			window->PreUpdate();
			obj->m_shader->Bind();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, obj->m_position);
			model *= glm::rotate(model, FrameTime::DeltaTime, glm::vec3(59.50f, 2.9f, 0.0045f));
			obj->m_shader->SetUniform("modelViewProjection", camera->GetViewPrrojection() * model);
			obj->m_contextbaseVA[index]->Bind();
			Renderer::GetAPI()->DrawIndexes(obj->m_indexBuffer->Count());	//DRAW HERE
			obj->m_shader->Unbind();
			obj->m_contextbaseVA[index]->Unbind();
			window->PostUpdate();
			index++;
		}
	}
}