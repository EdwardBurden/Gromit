#pragma once

#include "../RenderAPIs/RenderAPI.h"
#include "../RenderAPIs/Context.h"

namespace Gromit
{
	struct RenderObject
	{
		Shader* m_shader;
		std::vector<VertexArray*> m_contextbaseVA; //needs to be updated when the context windows changes
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
		Context* m_context;

		RenderObject(Shader* m_shader, const std::vector<VertexArray*>& m_contextbaseVA, VertexBuffer* m_vertexBuffer, IndexBuffer* m_indexBuffer, Context* m_context)
			: m_shader(m_shader), m_contextbaseVA(m_contextbaseVA), m_vertexBuffer(m_vertexBuffer), m_indexBuffer(m_indexBuffer), m_context(m_context)
		{
		}
	};
}