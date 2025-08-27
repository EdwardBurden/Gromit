#pragma once

#include "../AssetManagement/ShaderAsset.h"
#include "../AssetManagement/MeshAsset.h"
#include "../RenderAPIs/Context.h"
#include "../RenderAPIs/RenderAPI.h"
#include "Renderer.h"
#include "../ServiceLocator.h"
#include "RenderObject.h"

namespace Gromit
{
	class RenderCommands
	{
	public:
		static inline RenderObject* CreateRenderObject(Context* context/*, ShaderAsset* shader, MeshAsset* mesh*/)
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
					{ShaderDataType::Float3 , "color"},
					{ShaderDataType::Float2 , "uvs"}
				});
			const auto& manager = ServiceLocator::GetService<AssetManager>();
			ShaderAsset* vert = manager->GetAsset<ShaderAsset>(545);
			ShaderAsset* frag = manager->GetAsset<ShaderAsset>(123434);
			TextureAsset* smileTextureAsset = manager->GetAsset<TextureAsset>(345455675675);
			VertexArray* m_va[2];
			//////////////

			std::vector<VertexArray*> vArrays;
			auto smileTexture = Renderer::GetAPI()->CreateTexture(*smileTextureAsset);
			auto shader = Renderer::GetAPI()->CreateShader(*vert, *frag);
			auto m_tempVB = Renderer::GetAPI()->CreateVertexBuffer(vertices, sizeof(vertices));
			m_tempVB->SetLayout(layout);
			auto m_tempIB = Renderer::GetAPI()->CreateIndexBuffer(indices, sizeof(indices));
			for (Window* window : context->GetWindows())
			{
				window->Activate();
				auto va = Renderer::GetAPI()->CreateVertexArray();
				va->Bind();
				va->SetIndexBuffer(m_tempIB);
				va->SetVertexBuffer(m_tempVB);
				va->Unbind();
				vArrays.push_back(va);
			}
			RenderObject* robj = new RenderObject(shader, smileTexture, vArrays, m_tempVB, m_tempIB, context);
			return robj;
		}

		static inline void DrawRenderObject(RenderObject* obj)
		{
			int index = 0;
			for (auto window : obj->m_context->GetWindows())
			{
				window->PreUpdate();
				obj->m_shader->Bind();	
				obj->m_texture->Bind();
				obj->m_contextbaseVA[index]->Bind();
				Renderer::GetAPI()->DrawIndexes(obj->m_indexBuffer->Count());	//DRAW HERE
				obj->m_texture->Unbind();
				obj->m_shader->Unbind();
				obj->m_contextbaseVA[index]->Unbind();
				window->PostUpdate();
				index++;
			}

		}
	};
}