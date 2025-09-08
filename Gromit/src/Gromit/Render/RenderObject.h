#pragma once

#include "Math/Math.h"
#include "RenderAPIs/RenderAPIs.h"

namespace Gromit
{
	struct RenderObject
	{
		glm::vec3 m_position;
		glm::vec3 m_eulur;
		Shader* m_shader;
		Texture* m_texture;
		std::vector<VertexArray*> m_contextbaseVA; //needs to be updated when the context windows changes
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
		Context* m_context;

		RenderObject(Shader* m_shader,Texture* texture, const std::vector<VertexArray*>& m_contextbaseVA, VertexBuffer* m_vertexBuffer, IndexBuffer* m_indexBuffer, Context* m_context)
			: m_shader(m_shader), m_texture(texture), m_contextbaseVA(m_contextbaseVA), m_vertexBuffer(m_vertexBuffer), m_indexBuffer(m_indexBuffer), m_context(m_context)
		{
			m_position = glm::vec3(2, -2, -6);
		}
	};
}