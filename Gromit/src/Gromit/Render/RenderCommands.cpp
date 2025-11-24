#include "Render/RenderCommands.h"

namespace Gromit
{
	std::unique_ptr<RenderObject> RenderCommands::CreateRenderObject(const MeshRendererComponentInstance& meshInstance)
	{
		Material* material = Renderer::GetAPI()->CreateMaterial(meshInstance.material);
		VertexBuffer* vertexBuffer = Renderer::GetAPI()->CreateVertexBuffer(meshInstance.mesh->GetVertices(), meshInstance.mesh->GetVertexCount());
		IndexBuffer* indexBuffer = Renderer::GetAPI()->CreateIndexBuffer(meshInstance.mesh->GetIndices(), meshInstance.mesh->GetIndexCount());
		BufferLayout* bufferLayout = Renderer::GetAPI()->CreateBufferLayout(meshInstance.mesh->GetLayout());
		vertexBuffer->SetLayout(bufferLayout);

		VertexArray* vertexArray = Renderer::GetAPI()->CreateVertexArray();
		vertexArray->Bind();
		vertexArray->SetVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);
		material->Bind();
		vertexArray->Unbind();
		return std::make_unique<RenderObject>(material, vertexArray);
	}

	void RenderCommands::DrawRenderObject(const RenderObject& renderObject, const TransformComponentInstance& transform, Camera* camera) //todo pass in time plus other render params
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.m_position);	
		
		renderObject.m_material->Bind();
		renderObject.m_material->SetUniform("modelViewProjection", camera->GetViewPrrojection() * model);
		renderObject.m_vertexArray->Bind();
		renderObject.m_vertexArray->Draw();
		renderObject.m_material->Unbind();
		renderObject.m_vertexArray->Unbind();
	}


	/*RenderObject* RenderCommands::CreateRenderObject(std::shared_ptr<MaterialAsset> material, std::shared_ptr<MeshAsset>  mesh, BufferLayout* layout)
	{
		std::vector<VertexArray*> vArrays;
		auto materialGPU = Renderer::GetAPI()->CreateMaterial(material);
		//auto shader = Renderer::GetAPI()->CreateShader(*vert, *frag);
		auto m_tempVB = Renderer::GetAPI()->CreateVertexBuffer(mesh->GetVertices(), mesh->GetVertexCount());
		m_tempVB->SetLayout(layout);
		auto m_tempIB = Renderer::GetAPI()->CreateIndexBuffer(mesh->GetIndices(), mesh->GetIndexCount());
		for (Window* window : Context::SharedContext->GetWindows())
		{
			window->Activate(); //will be in render or main loop
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
	}*/
}