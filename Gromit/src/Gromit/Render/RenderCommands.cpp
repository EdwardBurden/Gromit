#include "Render/RenderCommands.h"

namespace Gromit
{
	RenderObject* RenderCommands::CreateRenderObject(std::shared_ptr<MaterialAsset> material, std::shared_ptr<MeshAsset>  mesh, BufferLayout* layout)
	{
		std::vector<VertexArray*> vArrays;
		auto materialGPU = Renderer::GetAPI()->CreateMaterial(material);
		//auto shader = Renderer::GetAPI()->CreateShader(*vert, *frag);
		auto m_tempVB = Renderer::GetAPI()->CreateVertexBuffer(mesh->GetVertices(), mesh->GetVertexCount());
		m_tempVB->SetLayout(layout);
		auto m_tempIB = Renderer::GetAPI()->CreateIndexBuffer(mesh->GetIndices(), mesh->GetIndexCount());
		for (Window* window : Context::SharedContext->GetWindows())
		{
			window->Activate();
			auto va = Renderer::GetAPI()->CreateVertexArray();
			va->Bind();
			va->SetIndexBuffer(m_tempIB);
			va->SetVertexBuffer(m_tempVB);
			materialGPU->Bind();
			va->Unbind();
			vArrays.push_back(va);
		}
		return new RenderObject(materialGPU, vArrays, m_tempVB, m_tempIB, Context::SharedContext); // pos needed
	}

	void RenderCommands::DrawRenderObject(RenderObject* obj, Camera* camera) //todo pass in time plus other render params
	{
		int index = 0;
		for (auto window : obj->m_context->GetWindows())
		{
			if (window == nullptr)
				continue;
			window->PreUpdate(); //tod move out 
			obj->m_material->Bind();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, obj->m_position);
			model *= glm::rotate(model, FrameTime::DeltaTime, glm::vec3(59.50f, 2.9f, 0.0045f));
			obj->m_material->SetUniform("modelViewProjection", camera->GetViewPrrojection() * model);
			obj->m_contextbaseVA[index]->Bind();
			Renderer::GetAPI()->DrawIndexes(obj->m_indexBuffer->Count());	//DRAW HERE
			obj->m_material->Unbind();
			obj->m_contextbaseVA[index]->Unbind();
			window->PostUpdate();
			index++;
		}
	}
}