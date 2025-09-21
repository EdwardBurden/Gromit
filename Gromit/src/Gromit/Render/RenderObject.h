#pragma once

#include "Math/Math.h"
#include "RenderAPIs/RenderAPIs.h"

namespace Gromit
{
	struct RenderObject
	{
		glm::vec3 m_position;
		glm::vec3 m_eulur;
		Material* m_material;
	//	Shader* m_shader;
	//	Texture* m_texture;
		std::vector<VertexArray*> m_contextbaseVA; //needs to be updated when the context windows changes
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
		Context* m_context;

		RenderObject(Material* m_mat, const std::vector<VertexArray*>& m_contextbaseVA, VertexBuffer* m_vertexBuffer, IndexBuffer* m_indexBuffer, Context* m_context)
			: m_material(m_mat), m_contextbaseVA(m_contextbaseVA), m_vertexBuffer(m_vertexBuffer), m_indexBuffer(m_indexBuffer), m_context(m_context)
		{
			m_position = glm::vec3(2, -2, -6);
		}
	};
}