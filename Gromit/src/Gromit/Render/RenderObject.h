#pragma once

#include "Math/Math.h"
#include "RenderAPIs/RenderAPIs.h"

namespace Gromit
{
	struct EmptyTest
	{

		EmptyTest() = default;
	};

	struct RenderObject
	{
		std::unique_ptr<Material> m_material;
		std::unique_ptr<VertexArray> m_vertexArray;
		//const VertexBuffer* m_vertexBuffer;
		//const IndexBuffer* m_indexBuffer;
		Context* m_context;

		RenderObject() = default;
		~RenderObject() = default;
		RenderObject(Material* material, VertexArray* vertexArray, Context* m_context) : m_material(material), m_vertexArray(vertexArray), m_context(m_context)
		{

		}
	};
}