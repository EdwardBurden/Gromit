#pragma once

#include "../AssetManagement/ShaderAsset.h"
#include "../AssetManagement/MeshAsset.h"
#include "../RenderAPIs/Context.h"
#include "../RenderAPIs/RenderAPI.h"
#include "Renderer.h"
#include "../ServiceLocator.h"
#include "RenderObject.h"
#include "Camera.h"
#include "../AssetManagement/MeshAsset.h"

namespace Gromit
{
	class RenderCommands
	{
	public:
		static inline RenderObject* CreateRenderObject(Context* context)
		{
			///////////////TEMP PART
			float vertices[] = {
				// positions          // colors           // texture coords
				 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
				 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
				-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
			};
			unsigned int indices[] = {  // note that we start from 0!
				0, 1, 3,  // first Triangle
				1, 2, 3   // second Triangle
			};
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
			RenderObject* robj = new RenderObject(shader, smileTexture, vArrays, m_tempVB, m_tempIB, context);
			update = 0;
			return robj;
		}

		static inline void DrawRenderObject(RenderObject* obj, Camera* camera)
		{
			int index = 0;
			for (auto window : obj->m_context->GetWindows())
			{
				window->PreUpdate();
				obj->m_shader->Bind();
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, obj->m_position);
				model *= glm::rotate(model, update, glm::vec3(0.05f, 0.2f,0.05f));
				obj->m_shader->SetUniform("modelViewProjection", camera->GetViewPrrojection() * model);
				obj->m_contextbaseVA[index]->Bind();
				Renderer::GetAPI()->DrawIndexes(obj->m_indexBuffer->Count());	//DRAW HERE
				obj->m_shader->Unbind();
				obj->m_contextbaseVA[index]->Unbind();
				window->PostUpdate();
				index++;
			}
			update +=0.0005f;
		}

		 static inline float update;
	};
}